/*
 * Tema 2 ASC
 * 2019 Spring
 * Catalin Olaru / Vlad Spoiala
 */
#include "utils.h"
#include <assert.h>

/* Copyright [2019] Gavan Adrian-George, 334CA */
double* my_solver(int N, double *A, double* B) {
	printf("OPT SOLVER\n");

	register int i = 0;
	register int j = 0;
	register int k = 0;

	/* Transpose of A */
	double *At = calloc(N * N, sizeof(double));
	assert(At != NULL && "At allocation failed");
	/* Transpose of B */
	double *Bt = calloc(N * N, sizeof(double));
	assert(Bt != NULL && "Bt allocation failed");
	/* Auxiliary matrix used to store
	 * At*B + Bt*A
	 */
	double *Aux = calloc(N * N, sizeof(double));
	assert(Aux != NULL && "Aux allocation failed");
	/* Result matrix */
	double *C = calloc(N * N, sizeof(double));
	assert(C != NULL && "C allocation failed");

	double *pAt;
	double *pBt;
	double *pA;
	double *pB;
	double *pC;
	double *pAux;
	double *pAux2;

	register double vAt;
	register double vBt;
	register double vAux;

	/* At and Bt */
	for (i = 0; i < N; i++) {
		pAt = &At[i * N];
		pBt = &Bt[i * N];
		for (j = 0; j < N; j++) {
			*(pAt + j) = A[j * N + i];
			*(pBt + j) = B[j * N + i];
		}
	}

	/* At * B + Bt * A */
	for (i = 0; i < N; i++) {
		pAt = &At[i * N];
		pAux = &Aux[i * N];
		pBt = &Bt[i * N];
		for (k = 0; k < N; k++) {
			vBt = *(pBt + k);
			pA = &A[k * N];
			vAt = *(pAt + k);
			pB = &B[k * N];
			/* Compute only elements from upper triangular matrix */
			for (j = i; j < N; j++) {
				*(pAux + j) += vBt * (*(pA + j)) + vAt * (*(pB + j));
			}
		}
	}

	/* (At * B + Bt * A) ^ 2 */
	for (i = 0; i < N; i++) {
		pC = &C[i * N];
		pAux = &Aux[i * N];
		for (k = 0; k < N; k++) {
			vAux = *(pAux + k);
			pAux2 = &Aux[k * N];
			/* Compute only elements from upper triangular matrix */
			for (j = i; j < N; j++) {
				*(pC + j) += vAux * (*(pAux2 + j));
			}
		}
	}

	/* Free allocated memory */
	free(Aux);
	free(At);
	free(Bt);

	return C;
}
