/*
 * Tema 2 ASC
 * 2019 Spring
 * Catalin Olaru / Vlad Spoiala
 */
#include "utils.h"
#include <assert.h>

/* Copyright [2019] Gavan Adrian-George, 334CA */
double* my_solver(int N, double *A, double* B) {
	printf("NEOPT SOLVER\n");
	int i = 0;
	int j = 0;
	int k = 0;

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

	/* At and Bt*/
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			At[j * N + i] = A[i * N + j];
			Bt[j * N + i] = B[i * N + j];
		}
	}

	/* At * B + Bt * A */
	for (i = 0; i < N; i++) {
		/* Compute only elements from upper triangular matrix */
		for (j = i; j < N; j++) {
			for (k = 0; k < N; k++) {
				Aux[i * N + j] += At[i * N + k] * B[k * N + j] +
									Bt[i * N + k] * A[k * N + j];
			}
		}
	}

	/* (At * B + Bt * A) ^ 2 */
	for (i = 0; i < N; i++) {
		/* Compute only elements from upper triangular matrix */
		for (j = i; j < N; j++) {
			for (k = 0; k < N; k++) {
				C[i * N + j] += Aux[i * N + k] * Aux[k * N + j];
			}
		}
	}

	/* Free allocated memory */
	free(Aux);
	free(At);
	free(Bt);

	return C;
}
