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

int fbfd = 0;		// Frame Buffer File Descriptor
struct fb_fix_screeninfo finfo;
struct fb_var_screeninfo vinfo_original;
struct fb_var_screeninfo vinfo;
long int screensize = 0;
char *fbuf = 0;		// Frame Buffer
char *bbuf;			// Back Buffer

int fb_sizeof_finfo(){
	return sizeof( struct fb_fix_screeninfo );
}

int fb_sizeof_vinfo(){
	return sizeof( struct fb_var_screeninfo );
}

// Open default framebuffer.
// Returns -1 if unsuccessful or the file descriptor if success
int fb_open_default() {
	int fbfd = open( "/dev/fb0", O_RDWR );
	return fbfd;
}

int fb_open() {
	fbfd = open( "/dev/fb0", O_RDWR );

	// Read fixed screen infromation
	if ( ioctl( fbfd, FBIOGET_FSCREENINFO, &finfo ) ) {
		printf("Error reading fixed screen info.\n");
		return(-1);
	}
	
	printf("Display info %dx%d, %d bpp\n", 
		vinfo.xres, vinfo.yres, 
		vinfo.bits_per_pixel );

	// Copy the original vinfo so we can restore later
	memcpy( &vinfo_original, &vinfo, sizeof(struct fb_fix_screeninfo));

	// Get the screen size
	//fb_load_finfo();
	// Read variable screen infromation
	if ( ioctl( fbfd, FBIOGET_VSCREENINFO, &vinfo ) ) {
		printf("Error reading variable screen info.\n");
		return(-1);
	}
	screensize = finfo.smem_len;
	
	// Map the frame buffer
	fbuf = (char*)mmap( 
		0, 
		screensize, 
		PROT_READ|PROT_WRITE, 
		MAP_SHARED, 
		fbfd, 
		0 );

	if ((int) fbuf==-1 ) {
		printf( "Failed to mmap\n" );
		return(-1);
	}

	// Create a back buffer
	bbuf = malloc( screensize );

//	fb_setbpp( 8 );
//	fb_save_vinfo( &vinfo );
		
	return( fbfd );
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
	printf( "  sizeof= %d\n",        sizeof( struct fb_fix_screeninfo ) );
	
	printf( "  ID: %s\n",           finfo->id );
	printf( "  SMEM_START: %d\n",   finfo->smem_start );
	printf( "  SMEM_LENGTH: %d\n",  finfo->smem_len );
	printf( "  TYPE: %d\n",         finfo->type );
	printf( "  TYPE_AUX: %d\n",     finfo->type_aux );
	printf( "  VISUAL: %d\n",       finfo->visual );
	printf( "  XPANSTEP: %d\n",     finfo->xpanstep );
	printf( "  YPANSTEP: %d\n",     finfo->ypanstep );
	printf( "  YWRAPSTEP: %d\n",    finfo->ywrapstep );
	printf( "  LINE-LENGTH: %d\n",  finfo->line_length );
	printf( "  MMIOSTART: %d\n",    finfo->mmio_start );
	printf( "  MMIO_LEN: %d\n",     finfo->mmio_len );
	printf( "  ACCEL: %d\n",        finfo->accel );
	printf( "  CAPABILITIES: %d\n", finfo->capabilities );
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
	printf( "  sizeof= %d\n",      sizeof( struct fb_var_screeninfo ) );
	printf( "  XRES: %d\n", vinfo->xres );
	printf( "  YRES: %d\n", vinfo->yres );
	printf( "  BPP:  %d\n", vinfo->bits_per_pixel );
	return(1);
}

int fb_close() {
	// Restore screen
	fb_save_vinfo( &vinfo_original );
	// Free the back and frame buffers
	free( bbuf );
	munmap( fbuf, screensize );
	// Close the framebuffer
	close( fbfd );
	fbfd = 0;
}
// Clear the backbuffer
int fb_cls( int color ) {
	memset( bbuf, color, vinfo.xres * vinfo.yres );
}
// Copy the back buffer to the frame buffer
int fb_flip() {
	memcpy( fbuf, bbuf, screensize );
}

int fb_getbpp() {
	return( vinfo.bits_per_pixel );
}
int fb_getheight() {
	return( vinfo.yres );
}
int fb_getwidth() {
	return( vinfo.xres );
}
int fb_plot( int x, int y, int color ) {
	// Calculate pixel position
	unsigned int pix = x + y * finfo.line_length;
	// Write pixel
	*((char*)(bbuf+pix)) = color; 
}
int fb_setbpp( int bpp ) {
	vinfo.bits_per_pixel = bpp;
}

int fb_save_vinfo( struct fb_var_screeninfo info ) {
	if (ioctl(fbfd, FBIOPUT_VSCREENINFO, &vinfo)) {
		printf("Error setting variable information.\n");
		return(0);
	}
	// Get fixed screen information
	if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
		printf("Error reading fixed information.\n");
	}
	return(1);
}

int fb_draw_line( int x1, int y1, int x2, int y2, int color ) {
}

int fb_draw_rect( int x, int y, int w, int h, int color ) {

}

int fb_fill_rect( int x, int y, int w, int h, int color ) {
	int xx, yy;
	for (yy=0; yy<h; yy++ ) {
		for (xx=0; xx<w; xx++ ) {
			fb_plot( x+xx, y+yy, color );
		}
	}
}


