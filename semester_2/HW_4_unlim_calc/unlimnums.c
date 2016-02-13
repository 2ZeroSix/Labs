#include "unlimnums.h"

static char* ba_error_message[4] = {"clear", "syntax error", "division by zero", "NULL pointer"};
static int ba_error_code = 0;
static char znfor; // inherited token, possible values: {'+', '-'}
static char forwardln = 0; //redirection info: if redirected: 1; else: 0

char* ba_error_info() {
	return ba_error_message[ba_error_code];
}

char ba_iscorrectform(const char* arg) {
	size_t i;
	for (i = 0; i < strlen(arg) - 1; i++) {
		if (!isdigit(arg[i])) {
			return 0;
		}
	}
	if ((arg[i] != '+') && (arg[i] != '-')) {
		return 0;
	}
	return 1;
}

char ba_isnormalform(const char* arg) {
	size_t i;
	if ((arg[0] != '+') && (arg[0] != '-') && ((arg[0] > 9) || (arg[0] < 0))) {
		return 0;
	}
	for(i = 1; i < strlen(arg); i++) {
		if(!isdigit(arg[i])) {
			return 0;
		}
	}
	return 1;
}

char ba_isbigger(const char* arg1, const char* arg2) {

}

const char* ba_sub(const char* arg1, const char* arg2) {
	char* res = NULL;
	if (!forwardln && !(arg1 && arg2)) {
		ba_error_code = 3;
	}
	else if(!forwardln && !(ba_iscorrectform(arg1) && ba_iscorrectform(arg2))) {
		ba_error_code = 1;
	}
	else {
		size_t l1 = strlen(arg1), l2 = strlen(arg2), lmax, lmin, i;
		char zn;
		//определение знака, длины выходной строки и вызов других операций по необходимости
		//если вызвана напрямую
		if(!forwardln) {
			if((arg1[l1-1] == '-') && (arg2[l2-1] == '+')) {
				forwardln = 1;
				znfor = '-';
				return ba_add(arg1,arg2)
			}
			else if((arg1[l1-1] == '+') && (arg2[l2-1] == '-')) {
				forwardln = 1;
				znfor = '+';
				return ba_add(arg1,arg2)
			}
			else if (l1 > l2) {
				if((arg1[l1-1] == '+') && (arg2[l2-1] == '+'))
				{
					res = (char*)malloc(sizeof(char)*l1);
					zn = '+';
				}
				else
				{
					res = (char*)malloc(sizeof(char)*l2);
					zn = '-';
				}
			}
			else if (l1 < l2) {
				if((arg1[l1-1] == '+') && (arg2[l2-1] == '+')) {
					res = (char*)malloc(sizeof(char)*l2);
					zn = '-';
				}
				else {
					res = (char*)malloc(sizeof(char)*l1);
					zn = '+';
				}
			}
			else {
				int j = l1 - 2;
				while (arg1[j] == arg2[j]) j--;
				if(j == -1) {
					return "0+";
				}
				else if (arg1[j] > arg2[j]) {
					if((arg1[l1-1] == '+') && (arg2[l2-1] == '+')) {
						res = (char*)malloc(sizeof(char)*l2);
						zn = '-';
					}
					else {
						res = (char*)malloc(sizeof(char)*l1);
						zn = '+';
					}
				}
				else {
					if((arg1[l1-1] == '+') && (arg2[l2-1] == '+')) {
						res = (char*)malloc(sizeof(char)*l2);
						zn = '-';
					}
					else {
						res = (char*)malloc(sizeof(char)*l1);
						zn = '+';
					}
				}
			}
		}
		//если вызвана из другой операции
		else {
			if (l1 > l2) {
				if((znfor[0] == '+') && (znfor[1] == '+'))
				{
					res = (char*)calloc(l1, sizeof(char));
					zn = '+';
				}
				else
				{
					res = (char*)calloc(l2, sizeof(char));
					zn = '-';
				}
			}
			else if (l1 < l2) {
				if((znfor[0] == '+') && (znfor[1] == '+')) {
					res = (char*)calloc(l2, sizeof(char));
					zn = '-';
				}
				else {
					res = (char*)calloc(l1, sizeof(char));
					zn = '+';
				}
			}
			else {
				int j = l1 - 2;
				while (arg1[j] == arg2[j]) j--;
				if(j == -1) {
					return "0+";
				}
				else if (arg1[j] > arg2[j]) {
					if((znfor[0] == '+') && (znfor[1] == '+')) {
						res = (char*)calloc(l2, sizeof(char));
						zn = '-';
					}
					else {
						res = (char*)calloc(l1, sizeof(char));
						zn = '+';
					}
				}
				else {
					if((znfor[0] == '+') && (znfor[1] == '+')) {
						res = (char*)calloc(l2, sizeof(char));
						zn = '-';
					}
					else {
						res = (char*)calloc(l1, sizeof(char));
						zn = '+';
					}
				}
			}
		}
		lmax = (l1>l2) ? l1 : l2;
		lmin = (l2>l1) ? l1 : l2;
		for (i = 0; i < lmin; i++) {
			if ()
		}
	}
	else {
		ba_error_code = 3;
	}
	forwardln = 0;
	return res;
}

const char* ba_add(const char* arg1, const char* arg2) {
	char* res = NULL;
	if (!forwardln && !(arg1 && arg2)) {
		ba_error_code = 3;
	}
	else if(!forwardln && !(ba_iscorrectform(arg1) && ba_iscorrectform(arg2))) {
		ba_error_code = 1;
	}
	else {
		size_t l1 = strlen(arg1), l2 = strlen(arg2), lmax, lmin, i;
		char zn;
		// определение знака и вызов других операций по необходимости
		// если вызвана напрямую
		if (!forwardln) {
			if (arg1[l1 - 1] == arg2[l2 - 1]) {
			 	zn = arg1[l1 - 1];
			}
			else {
				forwardln = 1;
				znfor = '+';
				if (arg1[l1 - 1] == '-') {
					return ba_sub(arg2, arg1);
				}
				else {
					return ba_sub(arg1, arg2);
				}
			}
		}
		//если вызвана из другой операции
		else {
			zn = znfor;
		}
		if (l1 > l2) {
			lmax = l1 + 1;
			lmin = l2;
		}
		else {
			lmax = l2 + 1;
			lmin = l1;
		}
		// printf("l1 %d\nl2 %d\nlmax %d\nlmin %d\n", l1, l2, lmax, lmin);
		res = (char*)calloc(lmax + 1,sizeof(char));
		for (i = 0; i <= lmax; i++)
			res[i] = 0;
		for (i = 0; i < (lmin - 1); i++) {
			res[i] += arg1[i] - '0' + arg2[i];
			if (res[i] > '9') {
				res[i] -= 10;
				res[i + 1] += 1;
			}
		}
		for (; i < (lmax - 2); i++) {
			res[i] += (l1 > l2) ? arg1[i] : arg2[i];
			if (res[i] > '9') {
				res[i] -= 10;
				res[i + 1] += 1;
			}
		}
		if (res[i] != 0)
			res[i++] += '0';
		res[i] = zn;
	}
	forwardln = 0;
	return res;
}
