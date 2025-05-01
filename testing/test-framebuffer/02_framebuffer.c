/*
**	Framebuffer functions for BlitzMax
**	(c) Copyright Si Dunford [Scaremonger], April 2025
*/

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

#include <brl.mod/blitz.mod/blitz.h>

struct FRAMEBUFFER_C {
	int fbfd;
	struct fb_fix_screeninfo finfo;
	struct fb_var_screeninfo vinfo;
	struct fb_var_screeninfo vcopy;
};

/*
struct BMX_FINFO {
	char id[16];        // Identification string
	BBINT smem_len;    // Size of screen buffer
	int line_length; // Length of a line in bytes
};

struct BMX_VINFO {
	int xres;       // visible resolution, X axis
	int yres;       // visuble resolution, Y axis
	int bits_per_pixel;			//Bits per pixel
} ;
*/

// Get the size of the C struct fb_fix_screeninfo
//BBINT fb_sizeof_fix_screeninfo(){
//	return sizeof( struct fb_fix_screeninfo );
//}

// Get the size of the C struct fb_var_screeninfo
//BBINT fb_sizeof_var_screeninfo(){
//	return sizeof( struct fb_var_screeninfo );
//}

// Get the size of FRAMEBUFFER_C
//BBINT fb_sizeof_FRAMEBUFFER(){
//	return sizeof( struct FRAMEBUFFER_C );
//}

// Open default framebuffer.
// Returns -1 if unsuccessful or the file descriptor if success
struct FRAMEBUFFER_C *fb_open( char *device ) {
//struct FRAMEBUFFER_C *fb_open() {
	struct FRAMEBUFFER_C *fb;
	fb = (struct FRAMEBUFFER_C*)malloc( sizeof( struct FRAMEBUFFER_C ) );

	// Open the Framebuffer
	//fb->fbfd = open( "/dev/fb0", O_RDWR );
	fb->fbfd = open( device, O_RDWR );
	if( fb->fbfd == -1 ) {
		//free( fb );
		return( 0 );
	};
	printf( "  descriptor:   %d\n", fb->fbfd );

	// Get Fixed screen information
	if ( ioctl( fb->fbfd, FBIOGET_FSCREENINFO, &fb->finfo ) ) {
		printf("- C: FINFO FAILED\n");
		free( fb );
		return( 0 );
	}
	//printf( "  line_length:  %d\n", fb->finfo.line_length );
	//finfo_dump( fb->finfo );

	// Get Variable screen information
	if ( ioctl( fb->fbfd, FBIOGET_VSCREENINFO, &fb->vinfo ) ) {
		printf("- C: VINFO FAILED\n");
		free( fb );
		return( 0 );
	}
	//vinfo_dump( fb->vinfo );
	
	// Save inital variable screen information for later
	memcpy( &fb->vcopy, &fb->vinfo, sizeof( struct fb_var_screeninfo ) );
	printf( "  C-Success " );
	return( fb );
}

void fb_close( struct FRAMEBUFFER_C *fb ) {
	if( !fb ) return;
	// Restore initial screen buffer
	if ( ioctl( fb->fbfd, FBIOPUT_VSCREENINFO, &fb->vcopy ) ) {
		printf("- C: VINFO WRITE FAILED\n");
	}		
	free( fb );
}


// Get Fixed Screen Information
// THis is read-only, so we shouldn't need to save it for restore
/*
BBINT fb_get_fix_screeninfo( int fbfd, struct fb_fix_screeninfo *finfo ) {

	printf("- C getting fixed screen info.\n");

	// Read fixed screen infromation
	if ( ioctl( fbfd, FBIOGET_FSCREENINFO, finfo ) ) {
		printf("- C: FAILED\n");
		return( BBFALSE );
	}
	return( BBTRUE );
}
*/

// Get Variable Screen Information
// We can use this to restore the initial settings
/*
BBINT fb_get_var_screeninfo( int fbfd, struct fb_var_screeninfo *vinfo ) {

	printf("- C getting variable screen info.\n");

	// Read fixed screen infromation
	if ( ioctl( fbfd, FBIOGET_VSCREENINFO, vinfo ) ) {
		printf("- C: FAILED\n");
		return( 0 );
	}
	return( 1 );
}
*/

// Get Fixed Screen Information
/*
BBINT fb_get_finfo( struct FRAMEBUFFER_C *fb, struct BMX_FINFO* pfinfo ) {

	//printf("fb_get_finfo()\n");
	if( !fb ) return( 0 );
//if( !finfo ) printf( "- finfo is NULL" );
//	if( !finfo ) return( 0 );
	
	//finfo_dump( &fb->finfo );
	
	printf( "  C: line_length:  %d\n", fb->finfo.line_length );
	struct BMX_FINFO finfo;
	finfo.line_length = fb->finfo.line_length;
	*pfinfo = finfo;
	// Copy C structure into BMX
	//finfo->id      = fb->finfo.id;
	//memcpy( finfo->id, &fb->finfo.id, 16 );
	//*pfinfo->smem_len    = 888; //fb->finfo.smem_len;
	//finfo->line_length = fb->finfo.line_length;
	return(1);
}
*/

// Get variable Screen Information
/*
BBINT fb_get_vinfo( struct FRAMEBUFFER_C *fb, struct BMX_VINFO* pvinfo ) {

	printf("fb_get_vinfo()\n");
if( !fb ) printf( "- fb0 is NULL" );
//if( !vinfo ) printf( "- vinfo is NULL" );
	
	if( !fb ) return( 0 );
//	if( !vinfo ) return( 0 );
	vinfo_dump( &fb->vinfo );
	
	printf( "XRES is: %d\n", fb->vinfo.xres );
	
	// Copy C structure into BMX
	struct BMX_VINFO vinfo;
	vinfo.xres            = fb->vinfo.xres;
	vinfo.yres            = fb->vinfo.yres;
	vinfo.bits_per_pixel  = fb->vinfo.bits_per_pixel;
	*pvinfo = vinfo;
	//*pvinfo->xres = 888; //fb->vinfo.xres;
	//vinfo->yres = 888; //fb->vinfo.yres;
	return(1);
}
*/

BBINT fb_get_bitsperpixel( struct FRAMEBUFFER_C *fb ) {
	if( !fb ) return( 0 );
	return fb->vinfo.bits_per_pixel;
}
BBINT fb_get_line_length( struct FRAMEBUFFER_C *fb ) {
	if( !fb ) return( 0 );
	return fb->finfo.line_length;
}
BBINT fb_get_xres( struct FRAMEBUFFER_C *fb ) {
	if( !fb ) return( 0 );
	return fb->vinfo.xres;
}
BBINT fb_get_yres( struct FRAMEBUFFER_C *fb ) {
	if( !fb ) return( 0 );
	return fb->vinfo.yres;
}

BBINT fb_get_res( struct FRAMEBUFFER_C *fb, BBINT *xres, BBINT *yres ) {
	if( !fb ) return( 0 );
	*xres = fb->vinfo.xres;
	*yres = fb->vinfo.yres;
	return 1;
}


// Internal debug function to dump fb_fix_screeninfo structure 
void finfo_dump( struct fb_fix_screeninfo *finfo ) {
	printf( "DUMP: fb_fix_screeninfo\n" );
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
}

// Internal debug function to dump fb_var_screeninfo structure 
void vinfo_dump( struct fb_var_screeninfo *vinfo ) {
	printf( "DUMP: fb_var_screeninfo\n");	
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
}

