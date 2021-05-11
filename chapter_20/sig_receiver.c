#define _GNU_SOURCE
#include <signal.h>
#include "signal_functions.h"
#include "tlpi_hdr.h"

static int sigCnt[NSIG];