#ifndef SPIKE_COMMON_H
#define SPIKE_COMMON_H



#define ALWAYS_ASSERT

#ifdef WIN32
typedef long long int64_t;
#endif



// ----------------------------------------------------------------------------
// If ALWAYS_ASSERT is defined, we make sure that  assertions are triggered 
// even if NDEBUG is defined.
// ----------------------------------------------------------------------------
#ifdef ALWAYS_ASSERT
// If NDEBUG is actually defined, remember this so
// we can restore it.
#  ifdef NDEBUG
#    define NDEBUG_ACTIVE
#    undef NDEBUG
#  endif
// Include the assert.h header file here so that it can
// do its stuff while NDEBUG is guaranteed to be disabled.
#  include <assert.h>
// Restore NDEBUG mode if it was active.
#  ifdef NDEBUG_ACTIVE
#    define NDEBUG
#    undef NDEBUG_ACTIVE
#  endif
#else
// Include the assert.h header file using whatever the
// current definition of NDEBUG is.
#  include <assert.h>
#endif


// ----------------------------------------------------------------------------


#define BURST_VALUE (1e-7)
#define BURST_NEW_VALUE (1e-4)


namespace spike {

const unsigned int BLOCK_SIZE = 512;

const unsigned int MAX_GRID_DIMENSION = 32768;

const unsigned int CRITICAL_THRESHOLD = 70;

enum KrylovSolverType {
	BiCGStab,
	BiCGStab2,
	CG
};

enum FactorizationMethod {
	LU_UL,
	LU_only
};

enum PreconditionerType {
	Spike,
	Block
};

inline
void kernelConfigAdjust(int &numThreads, int &numBlockX, const int numThreadsMax) {
	if (numThreads > numThreadsMax) {
		numBlockX = (numThreads + numThreadsMax - 1) / numThreadsMax;
		numThreads = numThreadsMax;
	}
}

inline
void kernelConfigAdjust(int &numThreads, int &numBlockX, int &numBlockY, const int numThreadsMax, const int numBlockXMax) {
	kernelConfigAdjust(numThreads, numBlockX, numThreadsMax);
	if (numBlockX > numBlockXMax) {
		numBlockY = (numBlockX + numBlockXMax - 1) / numBlockXMax;
		numBlockX = numBlockXMax;
	}
}


} // namespace spike


#endif
