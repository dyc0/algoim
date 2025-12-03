#ifndef LAPACK_MANGLING_H
#define LAPACK_MANGLING_H

/* * =======================================================================
 * AUTO-DETECTION LOGIC
 * =======================================================================
 */

/* * CASE 1: Windows (Microsoft Visual C++ or MinGW)
 * Windows is tricky. Standard Fortran (gfortran) on Windows usually adds 
 * an underscore (same as Linux). However, legacy systems or specific 
 * calling conventions might use UPPERCASE.
 * * We default to UNDERSCORE here because most modern open-source 
 * LAPACK binaries (OpenBLAS, R-Lapack) use it.
 */
#if defined(_WIN32) || defined(_WIN64)
    /* * If you are linking against a library that requires UPPERCASE 
     * (like some static MKL builds), uncomment the next line:
     */
    // #define LAPACK_GLOBAL(lcname, UCNAME) UCNAME
    
    /* Default Windows Behavior: Lowercase with Underscore */
    #define LAPACK_GLOBAL(lcname, UCNAME) lcname##_


/* * CASE 2: macOS and Linux (Unix-like systems)
 * These almost universally use lowercase with a trailing underscore.
 * This covers GCC, Clang, and Intel Compilers on Linux/Mac.
 */
#elif defined(__linux__) || defined(__APPLE__) || defined(__unix__)
    #define LAPACK_GLOBAL(lcname, UCNAME) lcname##_

/* * CASE 3: Fallback / Unknown
 * If we can't detect the OS, we default to the most common standard 
 * (underscore).
 */
#else
    #define LAPACK_GLOBAL(lcname, UCNAME) lcname##_
#endif


/* * =======================================================================
 * COMPLEX NUMBER HANDLING
 * =======================================================================
 * LAPACKE needs to know if it can use C99 complex types or if it 
 * needs to use a struct.
 */

#if defined(__STDC_IEC_559_COMPLEX__) || defined(__cplusplus)
    /* Modern C/C++ compilers support complex types naturally */
    #include <complex.h>
    #define LAPACK_COMPLEX_CUSTOM
    #define lapack_complex_float float _Complex
    #define lapack_complex_double double _Complex
#else
    /* Fallback for very old compilers: use a struct */
    /* (You usually don't need this branch for modern systems) */
    #define LAPACK_COMPLEX_STRUCTURE
#endif

#endif /* LAPACK_MANGLING_H */
