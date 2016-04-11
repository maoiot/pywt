/* Copyright (c) 2006-2012 Filip Wasilewski <http://en.ig.ma/> */
/* See COPYING for license details. */

#pragma once

#include "common.h"

/* Wavelet symmetry properties */
typedef enum {
    UNKNOWN = -1,
    ASYMMETRIC = 0,
    NEAR_SYMMETRIC = 1,
    SYMMETRIC = 2
} SYMMETRY;

/* Wavelet name */
typedef enum {
    HAAR,
    RBIO,
    DB,
    SYM,
    COIF,
    BIOR,
    DMEY,
    GAUS,
    MEXH,
    MORL,
    CGAU,
    SHAN,
    FBSP,
    CMOR
} WAVELET_NAME;


/* Wavelet structure holding pointers to filter arrays and property attributes */
typedef struct {
    double* dec_hi_double;  /* highpass decomposition */
    double* dec_lo_double;  /* lowpass decomposition */
    double* rec_hi_double;  /* highpass reconstruction */
    double* rec_lo_double;  /* lowpass reconstruction */
    float* dec_hi_float;
    float* dec_lo_float;
    float* rec_hi_float;
    float* rec_lo_float;

    size_t dec_len;   /* length of decomposition filter */
    size_t rec_len;   /* length of reconstruction filter */

    /* Wavelet properties */
    int vanishing_moments_psi;
    int vanishing_moments_phi;
    index_t support_width;

    SYMMETRY symmetry;

    unsigned int orthogonal:1;
    unsigned int biorthogonal:1;
    unsigned int compact_support:1;
    
    unsigned int dwt_possible:1;
    unsigned int cwt_possible:1;
    unsigned int complex_cwt:1;
    
    float lower_bound;
    float upper_bound;
    
    /* Parameters for shan, fbsp, cmor*/
    float center_frequency;
    float bandwidth_frequency;
    unsigned int fbsp_order;
    

    char* family_name;
    char* short_name;

} Wavelet;


/* 
 * Allocate Wavelet struct and set its attributes
 * name - (currently) a character codename of a wavelet family
 * order - order of the wavelet (ie. coif3 has order 3)
 */
Wavelet* wavelet(WAVELET_NAME name, unsigned int order);

/* 
 * Allocate blank Wavelet with zero-filled filters of given length
 */
Wavelet* blank_wavelet(size_t filters_length);

/* Deep copy Wavelet */
Wavelet* copy_wavelet(Wavelet* base);

/* 
 * Free wavelet struct. Use this to free Wavelet allocated with
 * wavelet(...) or blank_wavelet(...) functions.
 */
void free_wavelet(Wavelet *wavelet);
