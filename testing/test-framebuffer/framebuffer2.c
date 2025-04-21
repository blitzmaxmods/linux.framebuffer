// linux.h
// https://github.com/torvalds/linux/blob/master/include/linux/fb.h

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

int fb_sizeof_finfo(){
	return sizeof( struct fb_fix_screeninfo );
}

int fb_sizeof_vinfo(){
	return sizeof( struct fb_var_screeninfo );
}

// Open default framebuffer.
// Returns -1 if unsuccessful or the file descriptor if success
int fb_open() {
	int fbfd = open( "/dev/fb0", O_RDWR );
	return fbfd;
}

// Get Fixed Screen Information
int fb_get_finfo( int fbfd, struct fb_fix_screeninfo *finfo ) {

	printf("- C getting fixed screen info.\n");

	// Read fixed screen infromation
	if ( ioctl( fbfd, FBIOGET_FSCREENINFO, finfo ) ) {
		printf("- C: FAILED\n");
		return(0);
	}
	printf( "- C: SUCCESS\n");	
	printf( "  sizeof=%d\n", sizeof( struct fb_fix_screeninfo ) );
	
	printf( "  id:           %s\n", finfo->id );
	printf( "  smem_start:   %d\n", finfo->smem_start );
	printf( "  smem_len:     %d\n", finfo->smem_len );
	printf( "  type:         %d\n", finfo->type );
	printf( "  type_aux:     %d\n", finfo->type_aux );
	printf( "  visual:       %d\n", finfo->visual );
	printf( "  xpanstep:     %d\n", finfo->xpanstep );
	printf( "  ypanstep:     %d\n", finfo->ypanstep );
	printf( "  ywrapstep:    %d\n", finfo->ywrapstep );
	printf( "  line_length:  %d\n", finfo->line_length );
	printf( "  mmio_start:   %d\n",	finfo->mmio_start );
	printf( "  mmio_len:     %d\n", finfo->mmio_len );
	printf( "  accel:        %d\n", finfo->accel );
	printf( "  capabilities: %d\n", finfo->capabilities );
	printf( "  reserved:     %d,%d\n", finfo->reserved[0], finfo->reserved[1] );
	return(1);
}

// Get variable Screen Information
int fb_get_vinfo( int fbfd, struct fb_var_screeninfo *vinfo ) {

	printf("- C getting variable screen info.\n");

	// Read fixed screen infromation
	if ( ioctl( fbfd, FBIOGET_VSCREENINFO, vinfo ) ) {
		printf("- C: FAILED\n");
		return(0);
	}
	
	printf( "- C: SUCCESS\n");	
	printf( "  sizeof=%d\n", sizeof( struct fb_var_screeninfo ) );
	
	printf( "  xres:           %d\n", vinfo->xres );
	printf( "  yres:           %d\n", vinfo->yres );
	printf( "  xres_virtual:   %d\n", vinfo->xres_virtual );
	printf( "  yres_virtual:   %d\n", vinfo->yres_virtual );
	printf( "  xoffset:        %d\n", vinfo->xoffset );
	printf( "  yoffset:        %d\n", vinfo->yoffset );
	printf( "  bits_per_pixel: %d\n", vinfo->bits_per_pixel );
	printf( "  grayscale:      %d\n", vinfo->grayscale );
	printf( "  red:            %d,%d,%d\n", vinfo->red.offset, vinfo->red.length, vinfo->red.msb_right );
	printf( "  green:          %d,%d,%d\n", vinfo->green.offset, vinfo->green.length, vinfo->green.msb_right );
	printf( "  blue:           %d,%d,%d\n", vinfo->blue.offset, vinfo->blue.length, vinfo->blue.msb_right );
	printf( "  transp:         %d,%d,%d\n", vinfo->transp.offset, vinfo->transp.length, vinfo->transp.msb_right );
	printf( "  nonstd:         %d\n", vinfo->nonstd );
	printf( "  activate:       %d\n", vinfo->activate );
	printf( "  height:         %d\n", vinfo->height );
	printf( "  width:          %d\n", vinfo->width );
	printf( "  accel_flags:    %d\n", vinfo->accel_flags );
	printf( "  pixclock:       %d\n", vinfo->pixclock );
	printf( "  left_margin:    %d\n", vinfo->left_margin );
	printf( "  right_margin:   %d\n", vinfo->right_margin );
	printf( "  upper_margin:   %d\n", vinfo->upper_margin );
	printf( "  lower_margin:   %d\n", vinfo->lower_margin );
	printf( "  hsync_len:      %d\n", vinfo->hsync_len );
	printf( "  vsync_len:      %d\n", vinfo->vsync_len );
	printf( "  sync:           %d\n", vinfo->sync );
	printf( "  vmode:          %d\n", vinfo->vmode );
	printf( "  rotate:         %d\n", vinfo->rotate );
	printf( "  colorspace:     %d\n", vinfo->colorspace );
	printf( "  reserved:       %d,%d,%d,%d\n", vinfo->reserved[0], vinfo->reserved[1], vinfo->reserved[2], vinfo->reserved[3] );
	return(1);
}
