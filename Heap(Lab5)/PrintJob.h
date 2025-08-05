#pragma once

class PrintJob {
private:
  int priority;
  int jobNumber;
  int numPages;

public:
  PrintJob(int priority, int jobNum, int numPages);
  int getPriority() const;
  int getJobNumber() const;
  int getPages() const;
  //You can add additional functions here
};
