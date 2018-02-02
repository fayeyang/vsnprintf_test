#include  <linux/kernel.h>
#include  <linux/module.h>
#include  <linux/init.h>
#include  <linux/slab.h>
#include  <linux/vmalloc.h>

#include  <stdarg.h>

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "faye" );

char *cpBuf;

static int vaFunc( int i, ... ){
	int tmp;
	char *cptr;
	va_list arg_ptr;

	va_start( arg_ptr, i );
	for( tmp=0; tmp<i; tmp++ ){
		cptr = va_arg( arg_ptr, char* );
		printk( KERN_INFO "%dst arg is: %s\n", tmp, cptr );
	}
	va_end( arg_ptr );

	return 0;
}

static int __init vsnprintf_init( void ){

	unsigned long ulPa;
	int tmp;

	printk( "vsnprintf init!\n" );
	
	cpBuf = 0;
	cpBuf = ( char * )kzalloc( 50*sizeof(char), GFP_KERNEL );
	if( cpBuf == 0 ){
		printk( KERN_INFO "kmalloc failed!\n" );
		return 1;
	}
	printk( KERN_INFO "kmalloc addr:\t%lX\n", (unsigned long)cpBuf );
	ulPa = virt_to_phys( cpBuf );
	printk( KERN_INFO "kmalloc phyAddr:\t%lX\n", ulPa );
	
	tmp = vaFunc( 2, "the 1st str", "the 2st str" );
	
	tmp = vaFunc( 5, "aaa", "bbb", "ccc", "ddd", "eee", "fff" );
	
	return 0;
}
module_init( vsnprintf_init );


static void __exit vsnprintf_exit( void ){
	printk( KERN_INFO "vsnprintf exit!\n" );
	if( cpBuf != 0 ){
		kfree( cpBuf );
		printk( KERN_INFO "free cpBuf!\n" );
	}
}
module_exit( vsnprintf_exit );
