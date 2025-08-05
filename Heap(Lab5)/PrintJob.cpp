#include "PrintJob.h"

PrintJob::PrintJob (int setP, int setJ, int numP) : priority(setP), jobNumber(setJ), numPages(numP) {}

int PrintJob::getPriority() const {
    return priority;
}

int PrintJob::getJobNumber() const {
    return jobNumber;
}

int PrintJob::getPages() const {
    return numPages;
}
