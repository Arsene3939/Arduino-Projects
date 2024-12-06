#ifndef __CHAR
	#define __CHAR
#endif

#define _0 0x0000fe8282fe0000
#define _1 0x00000082fe800000 
#define _2 0x0000f292929e0000
#define _3 0x0000929292fe0000
#define _4 0x00001e1010fe0000
#define _5 0x00009e9292f20000
#define _6 0x0000fe9292f20000
#define _7 0x0000020202fe0000
#define _8 0x0000fe9292fe0000
#define _9 0x00009e9292fe0000

#define _a 0x00f08888f8800000
#define _b 0x00fe9090f0000000
#define _c 0x00f0909090000000
#define _d 0x0000f09090fe0000
#define _e 0x00f8a8a8a8b80000
#define _f 0x000008fe0a000000
#define _g 0x0000bca4a4fc0000
#define _h 0x00fe1010f0000000
#define _i 0x000000f400000000
#define _j 0x000080f400000000
#define _k 0x00fe205088000000
#define _l 0x000000fe00000000
#define _m 0x00f010f010f00000
#define _n 0x00f01010f0000000
#define _o 0x00f09090f0000000
#define _p 0x00fc24243c000000
#define _q 0x003c2424fc800000
#define _r 0x00f0201000000000
#define _s 0x00b8a8a8e8000000
#define _t 0x0004fe8400000000
#define _u 0x00f08080f0000000
#define _v 0x0070807000000000
#define _w 0x00f080f080f00000
#define _x 0x0088502050880000
#define _y 0x0000b8a0a0f80000
#define _z 0x00c8a8a898000000

#define _A 0x00fc262226fc0000
#define _B 0x00fe929292fc0000
#define _C 0x007cc68282820000
#define _D 0x00fe8282c67c0000
#define _E 0x00fe929292920000
#define _F 0x00fe121212020000
#define _G 0x00fe829292f20000
#define _H 0x00fe101010fe0000
#define _I 0x008282fe82820000
#define _J 0x00828282fe020000
#define _K 0x00fe102844820000
#define _L 0x00fe808080800000
#define _M 0x00fe02fc02fe0000
#define _N 0x00fe0c30c0fe0000
#define _O 0x007cc682c67c0000
#define _P 0x00fe2222223e0000
#define _Q 0x007cc6a246bc0000
#define _R 0x00fe2262e2be0000
#define _S 0x009e929292f20000
#define _T 0x000202fe02020000
#define _U 0x00fe808080fe0000
#define _V 0x003e60c0603e0000
#define _W 0x00fe80fe80fe0000
#define _X 0x00c66c106cc60000
#define _Y 0x000e18f0180e0000
#define _Z 0x00c2a2928a860000

#define _space 0x0000000000000000

long long int Alphabet(char x){
	switch(x){
		case 'a':return _a;
		case 'b':return _b;
		case 'c':return _c;
		case 'd':return _d;
		case 'e':return _e;
		case 'f':return _f;
		case 'g':return _g;
		case 'h':return _h;
		case 'i':return _i;
		case 'j':return _j;
		case 'k':return _k;
		case 'l':return _l;
		case 'm':return _m;
		case 'n':return _n;
		case 'o':return _o;
		case 'p':return _p;
		case 'q':return _q;
		case 'r':return _r;
		case 's':return _s;
		case 't':return _t;
		case 'u':return _u;
		case 'v':return _v;
		case 'w':return _w;
		case 'x':return _x;
		case 'y':return _y;
		case 'z':return _z;
		
		case 'A':return _A;
		case 'B':return _B;
		case 'C':return _C;
		case 'D':return _D;
		case 'E':return _E;
		case 'F':return _F;
		case 'G':return _G;
		case 'H':return _H;
		case 'I':return _I;
		case 'J':return _J;
		case 'K':return _K;
		case 'L':return _L;
		case 'M':return _M;
		case 'N':return _N;
		case 'O':return _O;
		case 'P':return _P;
		case 'Q':return _Q;
		case 'R':return _R;
		case 'S':return _S;
		case 'T':return _T;
		case 'U':return _U;
		case 'V':return _V;
		case 'W':return _W;
		case 'X':return _X;
		case 'Y':return _Y;
		case 'Z':return _Z;	
			
		case '0':return _0;
		case '1':return _1;	
		case '2':return _2;
		case '3':return _3;
		case '4':return _4;
		case '5':return _5;
		case '6':return _6;
		case '7':return _7;
		case '8':return _8;
		case '9':return _9;	
			
		case ' ':return _space;	
				
				
				
				
				
				
			
	}
}













