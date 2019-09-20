/*
 * Tema 2 ASC
 * 2019 Spring
 * Catalin Olaru / Vlad Spoiala
 */
#include "utils.h"
#include <cblas.h>
#include <assert.h>

/* Copyright [2019] Gavan Adrian-George, 334CA */
double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");

	/* Auxiliary matrix used to store
	 * At*B + Bt*A
	 */
	double *Aux = calloc(N * N, sizeof(double));
	assert(Aux != NULL && "Aux allocation failed");
	/* Result matrix */
	double *C = calloc(N * N, sizeof(double));
	assert(C != NULL && "C allocation failed");

	/* At * B + Bt * A */
	cblas_dsyr2k(CblasRowMajor, CblasUpper, CblasTrans, N, N, 1.0,
						A, N, B, N, 1.0, Aux, N);
	/* (At * B + Bt * A) ^ 2 */
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N,
						1.0, Aux, N, Aux, N, 0.0, C, N);

	/* Free allocated memory */
	free(Aux);

	return C;
}
