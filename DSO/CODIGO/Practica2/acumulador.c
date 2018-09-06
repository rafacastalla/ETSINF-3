#ifndef __KERNEL__
#  define __KERNEL__
#endif
#ifndef MODULE
#  define MODULE
#endif

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
MODULE_LICENSE("Dual BSD/GPL");

int n = 1;
module_param(n, int, S_IRUGO); //insmod ./acumulador.ko n=5

static int __init entrando(void) {
  printk(KERN_INFO "Entrando acumulador en el instante %d, n=%d\n",get_seconds(),n);
  return 0;
}

static void __exit saliendo(void) {
  printk(KERN_INFO "Saliendo acumulador en el instante %d, n=%d\n",get_seconds(),n);

}

module_init(entrando);
module_exit(saliendo);

int llevamos(void){
	return n;
}

void acumular(int i){
	n=n+i;
}
EXPORT_SYMBOL(acumular);
EXPORT_SYMBOL(llevamos);
