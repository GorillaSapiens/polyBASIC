// in development, so we're a little loosey goosey here...

#include <string>
#include <math.h>

#include "rational.hpp"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__)

#define ERR(x) std::string(x " at " AT)

#define BIGPOWEROF2 512

static sBIG_t gcd(sBIG_t x, sBIG_t y) {
   // euclid
   sBIG_t a = x;
   sBIG_t b = y;
   if (b == 0) {
      a = y;
      b = x;
   }
   if (b == 0) {
      throw (ERR("divide by zero in gcd"));
   }
   sBIG_t c = a % b;
   while (c != 0) {
      a = b;
      b = c;
      if (b == 0) {
         throw (ERR("divide by zero in gcd"));
      }
      c = a % b;
   }
   return b;
}

static sBIG_t lcm(sBIG_t x, sBIG_t y) {
   return (x * y) / gcd(x,y);
}

void Rational::simplify(void) {
   uBIG_t nn = (uBIG_t) whl * (uBIG_t) den + (uBIG_t) num;
   uBIG_t dd = (uBIG_t) den;

   uBIG_t g = gcd(nn,dd);
   nn /= g;
   dd /= g;

   if (dd == 0) {
      throw(ERR("divide by zero in simplify"));
   }
   whl = nn / dd;
   num = nn % dd;
   den = dd;
}

Rational::Rational() {
   sign = 1;
   whl = 0;
   num = 0;
   den = 1;
}

Rational::Rational(const Rational &orig) {
   sign = orig.sign;
   whl = orig.whl;
   num = orig.num;
   den = orig.den;
}

Rational& Rational::operator=(const Rational& other) {
   sign = other.sign;
   whl = other.whl;
   num = other.num;
   den = other.den;

   return *this;
}

Rational::Rational(int8_t s, uREG_t w, uREG_t n, uREG_t d) {
   assert(d != 0);
   assert(s == -1 || s == 1);
   sign = s;
   whl = w;
   num = n;
   den = d;

   simplify();
}

Rational::Rational(const char *p) {
   // i hate writing hand parsers

   p++; // skip the leading hash

   sign = 1;
   if (*p == '-') {
      sign = -1;
      p++;
   }
   if (*p == '+') {
      p++;
   }
   // ok
   char *tick = strchr((char *)p, '\'');
   char *slash = strchr((char *)p, '/');
   if (!tick) {
      if (!slash) {
         whl = atoi(p);
         num = 0;
         den = 1;
      }
      else {
         whl = 0;
         sscanf(p, "%ld/%ld", &num, &den);
      }
   }
   else {
      whl = atoi(p);
      sscanf(tick + 1, "%ld/%ld", &num, &den);
   }

   simplify();
}

Rational::Rational(double d) {
   whl = 0;
   sign = 1;
   if (d < 0.0) {
      sign = -1;
      d = -d;
   }
   if (d > 1.0) {
      whl = int(d);
      d -= (double)whl;
   }

   // and now the repeated fraction magic
   // https://en.wikipedia.org/wiki/Euler%27s_continued_fraction_formula
   double i = 1.0/d;
   sREG_t n = 1;
   sREG_t dens[1024];
   int spot = 0;
   while(isfinite(i) && i != 0 && n > 0 && n < (BIGPOWEROF2 >> spot)) {
      n = (sREG_t) i;
      i = i - (double)((sREG_t)i);
      i = 1.0 / i;
      if (n > 0 && n < (BIGPOWEROF2 >> spot)) {
         dens[spot++] = n;
      }
   }

   // a + b / c
   sREG_t a, b, c, nb, nc;
   b = 0;
   c = 1;

   while (spot > 0) {
      a = dens[--spot];
      nc = a * c + b;
      nb = c;
      c = nc;
      b = nb;
   }

   num = b;
   den = c;
}

Rational::Rational(int64_t i) {
   sign = 1;
   if (i < 0) {
      sign = -1;
      i = -i;
   }
   whl = i;
   num = 0;
   den = 1;
}

Rational Rational::operator + (Rational const & obj) const {
   Rational res;

   // TODO FIX can probably be done in a way that avoids overflow
   sBIG_t n =
      (((uBIG_t) whl *     (uBIG_t) den *     (uBIG_t) obj.den ) * (sBIG_t) sign) +
      (((uBIG_t) obj.whl * (uBIG_t) den *     (uBIG_t) obj.den ) * (sBIG_t) obj.sign) +
      (((uBIG_t) num *     (uBIG_t) obj.den                    ) * (sBIG_t) sign) +
      (((uBIG_t) obj.num * (uBIG_t) den                        ) * (sBIG_t) obj.sign);
   uBIG_t d = (uBIG_t) den * (uBIG_t) obj.den;

   int8_t s;
   if (n >= 0) {
      s = 1;
   }
   else {
      s = -1;
      n = -n;
   }

   uBIG_t g = gcd(n,d);
   n /= g;
   d /= g;

   res.sign = s;
   if (d == 0) {
      throw(ERR("divide by zero in operator +"));
   }
   res.whl = n / d;
   res.num = n % d;
   res.den = d;

   return res;
}

Rational Rational::operator - (Rational const & obj) const {
   Rational res;

   // TODO FIX can probably be done in a way that avoids overflow
   sBIG_t n =
      (((uBIG_t)whl     * (uBIG_t)den * (uBIG_t)obj.den) * (sBIG_t) sign) -
      (((uBIG_t)obj.whl * (uBIG_t)den * (uBIG_t)obj.den) * (sBIG_t) obj.sign) +
      (((uBIG_t)num     * (uBIG_t)obj.den)               * (sBIG_t) sign) -
      (((uBIG_t)obj.num * (uBIG_t)den)                   * (sBIG_t) obj.sign);
   uBIG_t d = den * obj.den;

   int8_t s;
   if (n >= 0) {
      s = 1;
   }
   else {
      s = -1;
      n = -n;
   }

   uBIG_t g = gcd(n,d);
   n /= g;
   d /= g;

   res.sign = s;
   if (d == 0) {
      throw(ERR("divide by zero in operator -"));
   }
   res.whl = n / d;
   res.num = n % d;
   res.den = d;

   return res;
}

Rational Rational::operator - () const {
   if (whl == 0 && num == 0) {
      return Rational(1, 0, 0, 1);
   }
   else {
      return Rational(-sign, whl, num, den);
   }
}

Rational Rational::operator * (Rational const & obj) const {
   Rational res;

   // TODO FIX can probably be done in a way that avoids overflow
   uBIG_t n =
      ((uBIG_t)whl     * (uBIG_t)obj.whl * (uBIG_t)den * (uBIG_t)obj.den) +
      ((uBIG_t)whl     * (uBIG_t)obj.num * (uBIG_t)den)  +
      ((uBIG_t)obj.whl * (uBIG_t)num     * (uBIG_t)obj.den)  +
      ((uBIG_t)num     * (uBIG_t)obj.num);
   uBIG_t d = (uBIG_t)den * (uBIG_t)obj.den;

   uBIG_t g = gcd(n,d);
   if (g == 0) {
      throw(ERR("divide by zero in operator *"));
   }
   n /= g;
   d /= g;

   int8_t s;
   if (sign == obj.sign) {
      s = 1;
   }
   else {
      s = -1;
   }

   res.sign = s;
   if (d == 0) {
      throw(ERR("divide by zero in operator *"));
   }
   res.whl = n / d;
   res.num = n % d;
   res.den = d;

   return res;
}

Rational Rational::operator / (Rational const & obj) const {
   Rational res;

   // TODO FIX can probably be done in a way that avoids overflow
   uBIG_t n =
      (uBIG_t)obj.den * ((uBIG_t)whl * (uBIG_t)den + (uBIG_t)num);
   uBIG_t d =
      (uBIG_t)den * ((uBIG_t)obj.whl * (uBIG_t)obj.den + (uBIG_t)obj.num);

   uBIG_t g = gcd(n,d);
   if (g == 0) {
      throw(ERR("divide by zero in operator /"));
   }
   n /= g;
   d /= g;

   int8_t s;
   if (sign == obj.sign) {
      s = 1;
   }
   else {
      s = -1;
   }

   res.sign = s;
   if (d == 0) {
      throw(ERR("divide by zero in operator /"));
   }
   res.whl = n / d;
   res.num = n % d;
   res.den = d;

   return res;
}

bool Rational::operator == (const Rational &other) const {
   sBIG_t l =
      ((sBIG_t) sign * ((sBIG_t) whl * (sBIG_t) den + (sBIG_t) num)) * (sBIG_t) other.den;
   sBIG_t r =
      ((sBIG_t) other.sign * ((sBIG_t) other.whl * (sBIG_t) other.den + (sBIG_t) other.num)) * (sBIG_t) den;
   return (l == r);
}

bool Rational::operator != (const Rational &other) const {
   sBIG_t l =
      ((sBIG_t) sign * ((sBIG_t) whl * (sBIG_t) den + (sBIG_t) num)) * (sBIG_t) other.den;
   sBIG_t r =
      ((sBIG_t) other.sign * ((sBIG_t) other.whl * (sBIG_t) other.den + (sBIG_t) other.num)) * (sBIG_t) den;
   return (l != r);
}


bool Rational::operator < (const Rational &other) const {
   sBIG_t l =
      ((sBIG_t) sign * ((sBIG_t) whl * (sBIG_t) den + (sBIG_t) num)) * (sBIG_t) other.den;
   sBIG_t r =
      ((sBIG_t) other.sign * ((sBIG_t) other.whl * (sBIG_t) other.den + (sBIG_t) other.num)) * (sBIG_t) den;
   return (l < r);
}

bool Rational::operator > (const Rational &other) const {
   sBIG_t l =
      ((sBIG_t) sign * ((sBIG_t) whl * (sBIG_t) den + (sBIG_t) num)) * (sBIG_t) other.den;
   sBIG_t r =
      ((sBIG_t) other.sign * ((sBIG_t) other.whl * (sBIG_t) other.den + (sBIG_t) other.num)) * (sBIG_t) den;
   return (l > r);
}


bool Rational::operator <= (const Rational &other) const {
   sBIG_t l =
      ((sBIG_t) sign * ((sBIG_t) whl * (sBIG_t) den + (sBIG_t) num)) * (sBIG_t) other.den;
   sBIG_t r =
      ((sBIG_t) other.sign * ((sBIG_t) other.whl * (sBIG_t) other.den + (sBIG_t) other.num)) * (sBIG_t) den;
   return (l <= r);
}

bool Rational::operator >= (const Rational &other) const {
   sBIG_t l =
      ((sBIG_t) sign * ((sBIG_t) whl * (sBIG_t) den + (sBIG_t) num)) * (sBIG_t) other.den;
   sBIG_t r =
      ((sBIG_t) other.sign * ((sBIG_t) other.whl * (sBIG_t) other.den + (sBIG_t) other.num)) * (sBIG_t) den;
   return (l >= r);
}

void Rational::print(char *buf, size_t buflen) const {
   snprintf(buf, buflen, "#%c%ld'%ld/%ld",
      sign > 0 ? '+' : '-', whl, labs(num), labs(den));
}

void Rational::shortprint(char *buf, size_t buflen) const {
   if (whl == 0 && num == 0) {
      snprintf(buf, buflen, "#0");
      return;
   }
   char mark[2] = {0, 0};
   if (sign < 0) {
      mark[0] = '-';
   }
   if (num == 0) {
      snprintf(buf, buflen, "#%s%ld", mark, whl);
      return;
   }
   if (whl == 0) {
      snprintf(buf, buflen, "#%s%ld/%ld", mark, num, den);
      return;
   }
   snprintf(buf, buflen, "#%s%ld'%ld/%ld", mark, whl, num, den);
}

Rational::operator double() const {
   return ((double)sign * ((double)whl + ((double)num / (double)den)));
}

Rational::operator sREG_t() const {
   return ((sREG_t)sign * (sREG_t)whl);
}

Rational Rational::abs(void) const {
   Rational ret(*this);
   ret.sign = 1;
   return ret;
}

Rational Rational::floor(void) const {
   Rational ret(*this);
   if (ret.sign > 0) { ret.num = 0; ret.den = 1; }
   if (ret.sign < 0 && ret.num > 0) { ret.whl++; ret.num = 0; ret.den = 1; }
   return ret;
}

int Rational::sgn(void) const {
   if(num == 0 && whl == 0) { return 0; }
   return sign;
}
