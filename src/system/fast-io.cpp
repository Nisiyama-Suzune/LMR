#define __ __attribute__ ((optimize ("-O3"))) 
#define _ __ __inline __attribute__ ((__gnu_inline__, __always_inline__, __artificial__)) 
namespace io {
	const int SIZE = 1000000; static char buf[SIZE + 1], *p = buf + SIZE;
	template <class t> _ bool read_int (t &x) {
		register int f = 0, sgn = 0; x = 0;
		while ((*p || (p = buf, buf[fread (buf, 1, SIZE, stdin)] = 0, buf[0])) && 
				(isdigit (*p) && (x = x * 10 + (*p - '0'), f = 1) || !f && (*p != '-' || (sgn = 1)))) ++p;
		if (sgn) x = -x;
		return f; }
	_ int read_str (char *x, int len, char d = '\n') {
		register int cnt = 0;
		while ((*p || (p = buf, buf[fread (buf, 1, SIZE, stdin)] = 0, buf[0])) && 
				cnt < len && *p != d) *(x++) = *(p++), ++cnt;
		if (*p == d) ++p;
		return cnt; }
//Set f to true to force an output (typically at the last write command).
	const int WSIZE = 1000000; static char wbuf[2 * WSIZE], *q = wbuf;
	__ void write (bool f, const char *str, ...) {
		va_list args; va_start (args, str);
		if ((q += vsprintf (q, str, args)) - wbuf >= WSIZE || f) fwrite (wbuf, 1, q - wbuf, stdout), q = wbuf;
		va_end (args); } }

