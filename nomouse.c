#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <X11/Xlib.h>


int
main(int argc, char **argv)
{
  char ch = 0, warp = 0;
  int rootx, rooty, winx, winy, offx = INT_MAX, offy = INT_MAX;
  unsigned int mask;
  Window ptroot, child;

  Display *disp = XOpenDisplay(NULL);
  if (disp == NULL) {
    fputs("nomouse: cannot open display.\n", stderr);
    exit(EXIT_FAILURE);
  }

  /* assume a single root window for simplicity */
  Window root = XRootWindow(disp, 0);
  Bool result = XQueryPointer(disp, root, &ptroot, &child,
                              &rootx, &rooty, &winx, &winy, &mask);
  if (result != True) {
    fputs("nomouse: cannot query pointer.\n", stderr);
    exit(EXIT_FAILURE);
  }

  while ((ch = getopt(argc, argv, "hvx:y:")) != -1) {
    switch (ch) {
    case 'x':
      offx = atoi(optarg);
      warp = 1;
      break;
    case 'y':
      offy = atoi(optarg);
      warp = 1;
      break;
    case 'v':
      fputs("version: nomouse development\n", stdout);
      exit(0);
    case 'h':
    default:
      fputs("usage: nomouse [-vh] [-x offset] [-y offset]\n", stderr);
      exit(EXIT_FAILURE);
    }
  }

  if (warp) {
    if (offx != INT_MAX) {
      rootx += offx;
    }
    if (offy != INT_MAX) {
      rooty += offy;
    }
    XWarpPointer(disp, None, root, 0, 0, 0, 0, rootx, rooty);
    XSetInputFocus(disp, PointerRoot, RevertToPointerRoot, CurrentTime);
  } else {
    fprintf(stdout, "%d, %d\n", rootx, rooty);
  }
  XCloseDisplay(disp);
  return 0;
}
