#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "intal.h"

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

static char *append_char(char *str, char c)
{
    int l = strlen(str);
    str[l] = c;
    str[l + 1] = '\0';
    return str;
}

static char *convert_to_zero(int n)
{
    char *z = (char *)malloc(n + 1);
    int i;
    for (i = 0; i < n; i++)
    {
        *(z + i) = '0';
    }
    *(z + n) = '\0';
    return z;
}

static char *append_zeros(char *n, int l)
{
    char *zeros = convert_to_zero(l);
    char *new_n = malloc(strlen(n) + l + 1);
    strcpy(new_n, zeros);
    strcat(new_n, n);
    free(zeros);
    return new_n;
}

static char *shift(char *str, int n)
{
    int l = strlen(str);
    char *new_str = malloc(l + n + 1);
    strcpy(new_str, str);
    char *zeros = convert_to_zero(n);
    strcat(new_str, zeros);
    free(zeros);

    return new_str;
}

void * intal_create(const char* str){
    int length = strlen(str);
    char * number = (char *)malloc(length+2);
    strcpy(number, str);
    int count = 0, c, i = 0;
	while((*(number + i) >= '0') && (*(number + i) <= '9'))
		i++;
	if (i != length){
		*(number + i) = '\0';
	}
	length = strlen(number);
    while(*(number + count) == '0'){
        count++;
    }
    if (count != length){
        c = count;
        while(*(number + c) >= '0' && *(number + c) <= '9'){
            c++;
        }
        if (c != length){
            return NULL;
        }
		char * num = malloc(length+2-count);
		strcpy(num, number + count);
		free(number);
        return num;
    }
    else {
        *number = '0';
        *(number + 1) = '\0';
        return number;
    }
}

void intal_destroy(void * intal){
	if(intal)
    	free(intal);
	return;
}

char * intal2str(void * intal){
    if (intal == NULL)
    {
        char *ret = malloc(4);
        strcpy(ret, "NaN");
        return ret;
    }

    char * str = (char *)malloc(strlen((char *)intal) + 1);
	int i = 0;
	while (*(char *)(intal + i) != '\0'){
		*(str + i) = *(char *)(intal + i);
		i++;
	}
	*(str + i) = '\0';
    return str;
}

void * intal_increment(void * intal){

	if (!intal)
		return NULL;
    int i, carry = 1;
    char answer;
    for (i = strlen(intal)-1; i >= 0; i--){
        answer = *(char *)(intal + i) + carry;
        if (answer <= '9'){
            *(char *)(intal + i) = answer;
            carry = 0;
            break;
        }
        else{
            answer = '0';
            *(char *)(intal + i) = answer;
        }
    }
    if (carry){
        char * new_intal = malloc(strlen(intal) + 2);
        strcpy(new_intal, "1");
        strcat(new_intal, intal);
        free(intal);
        return new_intal;
    }
    return intal;
}

void * intal_decrement(void * intal){
	if (!intal)
		return NULL;
    if (!strcmp(intal, "0")){
        return intal;
    }
    int i;
    char answer;
    for (i = strlen(intal)-1; i >= 0; i--){
        answer = *(char *)(intal + i) - 1;
        if (answer >= '0'){
            *(char *)(intal + i) = answer;
            break;
        }
        else{
            answer = '9';
            *(char *)(intal + i) = answer;
        }
    }
    void * new_intal = intal_create(intal);
    free(intal);
    return new_intal;
}

void *intal_add(void *intal1, void *intal2)
{
    if (!intal1 || !intal2)
        return NULL;
    int l1 = strlen(intal1), l2 = strlen(intal2);
    char *n1, *n2;
    if (l1 >= l2)
    {
        n1 = intal1;
        n2 = intal2;
    }
    else
    {
        n1 = intal2;
        n2 = intal1;
        int temp = l1;
        l1 = l2;
        l2 = temp;
    }
    int diff = l1 - l2, carry = 0, s, i;
    char *answer = (char *)malloc(l1 + 2);
    strcpy(answer, "");

    for (i = l2 - 1; i >= 0; i--)
    {
        s = *(char *)(n2 + i) - '0' + *(char *)(n1 + i + diff) - '0' + carry;
        answer = append_char(answer, (s % 10) + '0');
        carry = s / 10;
    }
    for (i = l1 - l2 - 1; i >= 0; i--)
    {
        s = *(char *)(n1 + i) - '0' + carry;
        answer = append_char(answer, (s % 10) + '0');
        carry = s / 10;
    }
    if (carry)
    {
        answer = append_char(answer, carry + '0');
    }
    answer = strrev(answer);
    void *ret = intal_create(answer);
    free(answer);
    return ret;
}

void *intal_diff(void *intal1, void *intal2)
{
    if (!intal1 || !intal2)
        return NULL;
    char *n1, *n2;
    int l1, l2;
    if (intal_compare(intal1, intal2) >= 0)
    {
        n1 = intal1;
        n2 = intal2;
    }
    else
    {
        n1 = intal2;
        n2 = intal1;
    }

    l1 = strlen(n1);
    l2 = strlen(n2);
    int d = l1 - l2, borrow = 0, i, sub;

    char *answer = (char *)malloc(l1 + 1);
    strcpy(answer, "");

    for (i = l2 - 1; i >= 0; i--)
    {
        sub = *(char *)(n1 + i + d) - *(char *)(n2 + i) - borrow;
        if (sub >= 0)
        {
            borrow = 0;
        }
        else
        {
            sub += 10;
            borrow = 1;
        }
        append_char(answer, sub + '0');
    }

    for (i = l1 - l2 - 1; i >= 0; i--)
    {
        if (*(char *)(n1 + i) == '0' && borrow)
        {
            append_char(answer, '9');
        }
        else
        {
            sub = *(char *)(n1 + i) - '0' - borrow;
            if (i > 0 || sub > 0)
                append_char(answer, sub + '0');
            borrow = 0;
        }
    }

    strrev(answer);
    char *ret = intal_create(answer);
    free(answer);
    return ret;
}

static char *mull_small(char *n1, char *n2)
{

    int num1 = atoi(n1);
    int num2 = atoi(n2);

    int result = num1 * num2;

    char *answer;
    answer = (char *)malloc(9);
    strcpy(answer, "");

    int flag = 0;
    while (result > 0)
    {
        append_char(answer, result % 10 + '0');
        result /= 10;
        flag = 1;
    }

    if (!flag)
    {
        strcpy(answer, "0");
        return answer;
    }

    strrev(answer);
    return answer;
}

void *intal_multiply(void *n1, void *n2)
{

    if (!n1 || !n2)
        return NULL;

    int l1 = strlen(n1);
    int l2 = strlen(n2);

    char *freeable;

    char *num1 = malloc(l1 + 1);
    char *num2 = malloc(l2 + 1);
    strcpy(num1, n1);
    strcpy(num2, n2);

    int n = l1;

    if (l1 > l2)
    {
        int d = l1 - l2;
        freeable = num2;
        num2 = append_zeros(num2, d);
        free(freeable);
    }
    else if (l2 > l1)
    {
        n = l2;
        int d = l2 - l1;
        freeable = num1;
        num1 = append_zeros(num1, d);
        free(freeable);
    }

    if (n == 0)
    {
        free(num1);
        free(num2);
        return "0";
    };
    if (n < 5)
    {
        free(num1);
        free(num2);
        return mull_small(n1, n2);
    }

    int f = n / 2;
    int mid = (n + 1) / 2;

    char *s1 = (char *)malloc(n + 1);
    char *s2 = (char *)malloc(n + 1);

    strcpy(s1, num1);
    strcpy(s2, num2);

    *(s1 + f) = '\0';
    char *new_num1 = num1 + f;

    *(s2 + f) = '\0';
    char *new_num2 = num2 + f;

    char *p1 = intal_multiply(s1, s2);
    char *p2 = intal_multiply(new_num1, new_num2);
    char *ab = intal_add(s1, new_num1);
    char *cd = intal_add(s2, new_num2);
    char *p3 = intal_multiply(ab, cd);
    char *t1 = shift(p1, 2 * mid);

    char *t2 = intal_add(p1, p2);

    freeable = t2;
    t2 = intal_diff(p3, t2);
    free(freeable);

    freeable = t2;
    t2 = shift(t2, mid);
    free(freeable);

    char *p4 = intal_add(t1, t2);
    char *p = intal_add(p2, p4);

    free(p1);
    free(p2);
    free(ab);
    free(cd);
    free(p3);
    free(t1);
    free(t2);
    free(p4);
    free(s1);
    free(s2);

    free(num1);
    free(num2);
    return p;
}

void *intal_divide(void *intal1, void *intal2)
{

    if (!intal1 || !intal2)
        return NULL;

    if (intal_compare(intal2, "0") == 0)
    {
        return NULL;
    }

    int cmp = intal_compare(intal1, intal2);
    if (cmp < 0)
    {
        return intal_create("0");
    }
    if (cmp == 0)
    {
        return intal_create("1");
    }

    int l1 = strlen(intal1);
    int l2 = strlen(intal2);

    char *answer = malloc(l1 + 1);
    *answer = '\0';

    char *freeable;

    char *pre = malloc(l1 + 1);
    strncpy(pre, intal1, l2);
    *(pre + l2) = '\0';

    if (intal_compare(pre, intal2) < 0)
    {
        strncpy(pre, intal1, l2 + 1);
        *(pre + l2 + 1) = '\0';
    }

    int i, count, len_pre, pre_len = strlen(pre);

    for (i = 0; i < (l1 - pre_len + 1); i++)
    {
        count = 0;

        while (intal_compare(pre, intal2) >= 0)
        {

            count++;
            freeable = pre;
            pre = intal_diff(pre, intal2);
            free(freeable);
        }
        append_char(answer, count + '0');

        if (i != l1 - pre_len)
        {
            len_pre = strlen(pre);
            char *new_pre = (char *)malloc(len_pre + 2);
            strcpy(new_pre, pre);
            append_char(new_pre, *(char *)(intal1 + pre_len + i));
            strcpy(pre, new_pre);
            free(new_pre);
            freeable = pre;
            pre = intal_create(pre);
            free(freeable);
        }
    }
    free(pre);
    return answer;
}

int intal_compare(void * intal1, void * intal2){
	if (!intal1 || !intal2)
		return 0;
    int l1 = strlen(intal1);
    int l2 = strlen(intal2);
    if (l1 > l2) return 1;
    else if (l1 < l2) return -1;
    int i;
    for (i = 0; i < l1; i++){
        if (*(char *)(intal1 + i) > *(char *)(intal2 + i)){
            return 1;
        }
        else if (*(char *)(intal1 + i) < *(char *)(intal2 + i)){
            return -1;
        }
    }
    return 0;
}




void * intal_pow(void *i1, void *i2){

	if (!i1 || !i2)
		return NULL;

	char * intal1 = malloc(strlen(i1)+1);
	char * intal2 = malloc(strlen(i2)+1);
	strcpy(intal1, i1);
	strcpy(intal2, i2);

    char * result = malloc(2);
	*result = '1';
	*(result+1) = '\0';

	char * freeable;
	
	if (!strcmp(intal1, "0"))
		return intal_create("0");

    while (intal_compare(intal2, "0") > 0){
        if (*(char *)(intal2+strlen(intal2)-1) % 2 != 0){
			freeable = result;
            result = intal_multiply(intal1, result);
			free(freeable);
        }
		freeable = intal2;
        intal2 = intal_divide(intal2, "2");
		free(freeable);
		freeable = intal1;
        intal1 = intal_multiply(intal1, intal1);
		free(freeable);
    }
	
	free(intal1);
	free(intal2);
	freeable = result;
	result = intal_create(result);
	free(freeable);

    return result;
}