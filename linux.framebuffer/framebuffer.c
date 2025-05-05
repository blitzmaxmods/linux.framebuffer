/*  /
   / Framebuffer functions for BlitzMax
  /  (c) Copyright Si Dunford [Scaremonger], April 2025
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

const int FB_OPEN_FAIL = 0x0001;
const int FB_MMAP_FAIL = 0x0002;

struct FRAMEBUFFER_C {
	int fbfd;
	int lasterr;
	struct fb_fix_screeninfo finfo;
	struct fb_var_screeninfo vinfo;
	struct fb_var_screeninfo vcopy;
	//long int screensize;	// Size of the fbuf
	char *fbuf;				// Frame buffer
	char *bbuf;				// Back buffer
	
	int bytespp;			// Bytes per pixel
	int datasize;			// Size of the data buffers
	int stride;				// Bytes between X position on different row
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
		fb->lasterr = FB_OPEN_FAIL;
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

	// Calcualtions
	//fb->screensize = fb->finfo.smem_len;
	fb->bytespp    = fb->vinfo.bits_per_pixel / 8;
	//fb->datasize   = fb->vinfo.xres * fb->vinfo.yres * fb->bytespp;
	fb->datasize   = fb->vinfo.yres * fb->finfo.line_length;
	fb->stride     = fb->finfo.line_length;
	
	// Map the frame buffer
	//fb->fbuf = (char*)mmap( 
	//	0, 
	//	fb->screensize, 
	//	PROT_READ|PROT_WRITE, 
	//	MAP_SHARED, 
	//	fb->fbfd, 
	//	0 );
	fb->fbuf = (char*)mmap( 
		0, 
		fb->datasize, 
		PROT_READ|PROT_WRITE, 
		MAP_SHARED, 
		fb->fbfd, 
		0 );
		
	if ((int) fb->fbuf==-1 ) {
		printf( "Failed to mmap\n" );
		fb->lasterr = FB_MMAP_FAIL;
		return( 0 );
	}
	
	// Create a back buffer
	//fb->bbuf = malloc( fb->screensize );
	fb->bbuf = malloc( fb->datasize );
	
	printf( "  C-Success " );
	return( fb );
}

void fb_close( struct FRAMEBUFFER_C *fb ) {
	if( !fb ) return;
	// Restore initial screen buffer
	if ( ioctl( fb->fbfd, FBIOPUT_VSCREENINFO, &fb->vcopy ) ) {
		printf("- C: VINFO WRITE FAILED\n");
	}
	// Unmap the framebuffer
	//munmap( fb->fbuf, fb->screensize );
	munmap( fb->fbuf, fb->datasize );
	close( fb->fbfd );
	fb->fbfd = 0;
	free( fb );
}

// Clear the backbuffer
int fb_cls( struct FRAMEBUFFER_C *fb, unsigned int color ) {
	//memset( fb->bbuf, color, fb->vinfo.xres * fb->vinfo.yres );
	memset( fb->bbuf, color, fb->datasize );
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

// Flip framebuffer for a backbuffer
//void fb_flip( struct FRAMEBUFFER_C *fb, char *bbuf ) {
//	memcpy( fb->fbuf, bbuf, fb->screensize );
//}

// Copy the back buffer to the frame buffer
int fb_flip( struct FRAMEBUFFER_C *fb ) {
	//memcpy( fb->fbuf, fb->bbuf, fb->screensize );
	memcpy( fb->fbuf, fb->bbuf, fb->datasize );
}

// BASIC PLOT
// THIS IS INEFFICIENT IF CALLED REPEATEDLY

int fb_plot( struct FRAMEBUFFER_C *fb, int x, int y, unsigned int color ) {
	// Calculate pixel position
	unsigned int pix = x * fb->stride + y * fb->bytespp;
	// Write pixel
	// *((char*)(fb->bbuf+pix)) = color;
	fb_putpixel( fb, pix, color );
}

// Plot a pixel
int fb_putpixel( struct FRAMEBUFFER_C *fb, unsigned int pix, unsigned int color ) {
	char* argb;
	switch( fb->vinfo.bits_per_pixel ) {
	//case 1:
	case 8:		// 
		argb = (char*)&color;
		*((char*)(fb->bbuf+pix)) = argb[0];		
		break;	
	case 16:	// RGB565
		argb = (char*)&color;
		//*((char*)(fb->bbuf+pix)) = argb[0];		
		//*((char*)(fb->bbuf+pix+1)) = argb[1];
		*((unsigned short*)(fb->bbuf+pix)) = color;
		break;	
	case 32:	// +0=B, +1=G, +2=R, +3=A
		*((unsigned int*)(fb->bbuf+pix)) = color;
		break;	
	default:
		printf( "fb_putpixel() not implemented for %dbpp devices\n", fb->vinfo.bits_per_pixel );
		break;
	}	
}

// Colour correct based on the bpp
unsigned int fb_color_forbpp( struct FRAMEBUFFER_C *fb, unsigned int color ) {
	char* argb;		// BGRA
	switch( fb->vinfo.bits_per_pixel ) {
	//case 1:
	case 8:		// Lookup value in colour table
// COLOUR TABLE NOT IMPLEMENTED
		argb = (char*)&color;
		return argb[3];	
		break;	
	case 16:	// Convert to RGB565
		argb = (char*)&color;
		return (((unsigned int)argb[2] & 0xF8) <<8 ) | (((unsigned int)argb[1] & 0xFC) <<3 ) | (argb[0] >>3);
		break;
	}
	// For 32bpp and anything else we just return the color
	return color;
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

