#include <stdio.h>
#include <stdlib.h>

static void options(int argc, char *argv[]);
static inline void unable_to_write(void);

static FILE *in, *out;

int main(int argc, char *argv[]) {
	options(argc, argv);

	enum token {
		N, NEWLINE = N,
		D, DOUBLE = D,
		S, SLASH = S,
		H, HIGH = H,
		A, ASTERISK = A,
		C, CHAR = C,
		MAX_TOKEN
	};

	enum effect {
		PUT,
		ESC
	};

	enum state {
		CODE, /* code */
		STRN, /* string */
		MBCM, /* maybe comment */
		CCOM, /* C comment */
		MBCD, /* maybe code */
		CPPC, /* C++ comment */
		MAX_STATE
	};

	typedef struct transition {
		enum state next;
		enum effect effect;
	}
	transition;

	transition table[MAX_STATE][MAX_TOKEN] = {
		/*                NEWLINE,         DOUBLE,          SLASH,           HIGH,       ASTERISK,           CHAR */
		[CODE] = { [N]={CODE,PUT}, [D]={STRN,PUT}, [S]={MBCM,PUT}, [H]={CODE,ESC}, [A]={CODE,PUT}, [C]={CODE,PUT} },
		[STRN] = { [N]={STRN,PUT}, [D]={CODE,PUT}, [S]={STRN,PUT}, [H]={STRN,ESC}, [A]={STRN,PUT}, [C]={STRN,PUT} },
		[MBCM] = { [N]={CODE,PUT}, [D]={CODE,PUT}, [S]={CPPC,PUT}, [H]={CODE,PUT}, [A]={CCOM,PUT}, [C]={CODE,PUT} },
		[CCOM] = { [N]={CCOM,PUT}, [D]={CCOM,PUT}, [S]={CCOM,PUT}, [H]={CCOM,PUT}, [A]={MBCD,PUT}, [C]={CCOM,PUT} },
		[MBCD] = { [N]={CCOM,PUT}, [D]={CCOM,PUT}, [S]={CODE,PUT}, [H]={CCOM,PUT}, [A]={CCOM,PUT}, [C]={CCOM,PUT} },
		[CPPC] = { [N]={CODE,PUT}, [D]={CPPC,PUT}, [S]={CPPC,PUT}, [H]={CPPC,PUT}, [A]={CPPC,PUT}, [C]={CPPC,PUT} }
	};

	int c;
	transition state = {CODE, PUT};

	while (c = getc(in), c != EOF) {
		enum token t;

		switch (c) {
		case '*':  t = ASTERISK; break;
		case '"':  t = DOUBLE;   break;
		case '/':  t = SLASH;    break;
		case '\n': t = NEWLINE;  break;
		default:   t = (c & 128) ? HIGH : CHAR; break;
		}

		state = table[state.next][t];

		switch (state.effect) {
		case PUT:
			if (EOF == putc(c, out))
				unable_to_write();
			break;
		case ESC:
			if (4 > fprintf(out, "\\%o", (unsigned char) c))
				unable_to_write();
			break;
		}
	}

	if (ferror(in)) {
		perror("Unable to read from source file");
		exit(EXIT_FAILURE);
	}
 
	exit(EXIT_SUCCESS);
}

static void options(int argc, char *argv[]) {
	if (argc == 1) {
		in = stdin;
		out = stdout;
		return;
	}
 
	if (argc != 3) {
		fprintf(stderr, "Expected either 0 or 2 arguments.\n");
		exit(EXIT_FAILURE);
	}
	if (!(in = fopen(argv[1], "r"))) {
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	if (!(out = fopen(argv[2], "w"))) {
		perror(argv[2]);
		exit(EXIT_FAILURE);
	}
 
	return;
}

static inline void unable_to_write(void) {
	perror("Unable to write to destination file");
	exit(EXIT_FAILURE);
}
