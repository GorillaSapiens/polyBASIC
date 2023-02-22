// in development, so we're a little loosey goosey here...

#include <string>

#include "rational.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__)

#define ERR(x) std::string(x " at " AT)

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

Rational Rational::operator + (Rational const & obj) {
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

Rational Rational::operator - (Rational const & obj) {
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

Rational Rational::operator * (Rational const & obj) {
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

Rational Rational::operator / (Rational const & obj) {
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

bool Rational::operator == (const Rational &other) {
   sBIG_t l =
      ((sBIG_t) sign * ((sBIG_t) whl * (sBIG_t) den + (sBIG_t) num)) * (sBIG_t) other.den;
   sBIG_t r =
      ((sBIG_t) other.sign * ((sBIG_t) other.whl * (sBIG_t) other.den + (sBIG_t) other.num)) * (sBIG_t) den;
   return (l == r);
}

bool Rational::operator != (const Rational &other) {
   sBIG_t l =
      ((sBIG_t) sign * ((sBIG_t) whl * (sBIG_t) den + (sBIG_t) num)) * (sBIG_t) other.den;
   sBIG_t r =
      ((sBIG_t) other.sign * ((sBIG_t) other.whl * (sBIG_t) other.den + (sBIG_t) other.num)) * (sBIG_t) den;
   return (l != r);
}


bool Rational::operator < (const Rational &other) {
   sBIG_t l =
      ((sBIG_t) sign * ((sBIG_t) whl * (sBIG_t) den + (sBIG_t) num)) * (sBIG_t) other.den;
   sBIG_t r =
      ((sBIG_t) other.sign * ((sBIG_t) other.whl * (sBIG_t) other.den + (sBIG_t) other.num)) * (sBIG_t) den;
   return (l < r);
}

bool Rational::operator > (const Rational &other) {
   sBIG_t l =
      ((sBIG_t) sign * ((sBIG_t) whl * (sBIG_t) den + (sBIG_t) num)) * (sBIG_t) other.den;
   sBIG_t r =
      ((sBIG_t) other.sign * ((sBIG_t) other.whl * (sBIG_t) other.den + (sBIG_t) other.num)) * (sBIG_t) den;
   return (l > r);
}


bool Rational::operator <= (const Rational &other) {
   sBIG_t l =
      ((sBIG_t) sign * ((sBIG_t) whl * (sBIG_t) den + (sBIG_t) num)) * (sBIG_t) other.den;
   sBIG_t r =
      ((sBIG_t) other.sign * ((sBIG_t) other.whl * (sBIG_t) other.den + (sBIG_t) other.num)) * (sBIG_t) den;
   return (l <= r);
}

bool Rational::operator >= (const Rational &other) {
   sBIG_t l =
      ((sBIG_t) sign * ((sBIG_t) whl * (sBIG_t) den + (sBIG_t) num)) * (sBIG_t) other.den;
   sBIG_t r =
      ((sBIG_t) other.sign * ((sBIG_t) other.whl * (sBIG_t) other.den + (sBIG_t) other.num)) * (sBIG_t) den;
   return (l >= r);
}

void Rational::print(char *buf) {
   sprintf(buf, "#%c%ld'%ld/%ld", sign > 0 ? '+' : '-', whl, labs(num), labs(den));
}

void Rational::prettyprint(char *buf) {
   if (whl == 0 && num == 0) {
      sprintf(buf, "#0");
      return;
   }
   if (sign < 0) {
      sprintf(buf, "#-");
   }
   else {
      sprintf(buf, "#");
   }
   if (num == 0) {
      sprintf(buf + strlen(buf), "%ld", whl);
      return;
   }
   if (whl == 0) {
      sprintf(buf + strlen(buf), "%ld/%ld", num, den);
      return;
   }
   sprintf(buf + strlen(buf), "%ld'%ld/%ld", whl, num, den);
}

Rational::operator double() const {
   return ((double)sign * ((double)whl + ((double)num / (double)den)));
}

void Rational::abs(void) {
   sign = 1;
}

void Rational::floor(void) {
   if (sign > 0) { num = 0; den = 1; }
   if (sign < 0 && num > 0) { whl++; num = 0; den = 1; }
}

int Rational::sgn(void) {
   if(num == 0 && whl == 0) { return 0; }
   return sign;
}
