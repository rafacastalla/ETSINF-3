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

int llevamos(void);
void acumular(int i);

int n = 1;
module_param(n, int, S_IRUGO); //insmod ./cliente.ko n=5

static int __init entrando(void) {
  printk(KERN_INFO "Entrando cliente con valor de n=%d\n",n);
  acumular(n);
  return 0;
}

static void __exit saliendo(void) {
	printk(KERN_INFO "Saliendo cliente con valor del acumulador n=%d\n",llevamos());
}

module_init(entrando);
module_exit(saliendo);
