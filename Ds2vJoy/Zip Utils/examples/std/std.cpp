#include <stdio.h>
#include "../../zip.h"
#include "../../unzip.h"



int main()
{ HZIP hz;

  hz = CreateZip("std1.zip",0);
  ZipAdd(hz,"znsimple.jpg", "std_sample.jpg");
  ZipAdd(hz,"znsimple.txt", "std_sample.txt");
  CloseZip(hz);

  hz = OpenZip("std1.zip",0);
  ZIPENTRY ze; GetZipItem(hz,-1,&ze); int numitems=ze.index;
  for (int zi=0; zi<numitems; zi++)
  { GetZipItem(hz,zi,&ze);
    UnzipItem(hz,zi,ze.name);
  }
  CloseZip(hz);

  return 0;
}

