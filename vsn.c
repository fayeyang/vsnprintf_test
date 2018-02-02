#include  <linux/kernel.h>
#include  <linux/module.h>
#include  <linux/init.h>
#include  <linux/slab.h>
#include  <linux/vmalloc.h>

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "faye" );

	char *cpBuf;

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
	
	tmp = 
	
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
