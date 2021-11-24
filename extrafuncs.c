#include "defs.h"

int sum_func(char* string){
	int sum = 0, k = 1;
	for (int i = 0; string[i] != '\0'; i++){
		sum += k*string[i];
		k *= -1;
	}
	if (sum > 0)	return sum;
	else			return -1*sum;
}

int power_func(int base, int power){
	int result = 1;
	if (power >= 0){
		for(int i = 0; i < power; i++){
			result *= base;
		}
		return result;
	}
	else{
		for(int i = power; i < 0; i++){
			result /= base;
		}
		return result;
	}
}

int eq_check(char* s1, char* s2){
	int i = 0;
	while(1){
		if (s1[i] == '\0' && s2[i] == '\0')	return 1;
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')	return 0;
		i++; 
	}
}