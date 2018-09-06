#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/io.h>
#include <asm/uaccess.h>
MODULE_LICENSE("Dual BSD/GPL");
//Las rutinas para acceder a los puertos de E/S residen en /usr/src/linux/include/asm/io.h y son macros, de modo que basta con incluir el fichero para poder usarlas
//Para acceder a los puertos desde un programa C fuera del núcleo, hay que ser superusuario y, además, requerir del sistema operativo el permiso para hacerlo ioperm() o iopl()

#ifndef __KERNEL__
#  define __KERNEL__
#endif
#ifndef MODULE
#  define MODULE
#endif

#define MAYOR_NUMBER 55
#define PUERTO_BASE 0xc030
#define RANGO 2

char mostrar = 0x00;
static int mayor = -1;
const char *device_name = "practica";


//La E/S propiamente dicha se realiza a través de la función inb(0xc030),
//que devuelve el valor (de 5 bits) al que se encuentra el puerto correspondiente
//y de la función outb(valor,puerto), que vuelca un valor de 8 bits sobre un puerto

int practica_open (struct inode *inode, struct file *filp){
  try_module_get(THIS_MODULE);
  return 0;
}

int practica_release (struct inode *inode, struct file *filp){
  module_put(THIS_MODULE);
  return 0;
}
// Estan en este orden !S7->11 S6->10 S5->12 S4->13 S3->15
//Los que interesan son los puertos 10,11,12 y 13
//ESTADO (S3-S7)
//dirección base 0xc030
//registro de datos está en 0xc030, el de estado en 0xc031 y el de control en 0xc032

ssize_t practica_read (struct file *filp, char *buf, size_t count, loff_t *offp){

    char aux = (unsigned char) inb(PUERTO_BASE+1);
    //S6->10
    if(count > 1 & (aux & 0x40) == 0x40){//S6 0100 0000
      *buf++ = '1';
    }else{
      *buf++ = '0';
    }
    //!S7->11
    if(count > 2 & (aux & 0x80) == 0x80) {//S7 1000 0000
      *buf++ = '0';
    }else{
      *buf++ = '1';
    }
    //S5->12
    if(count > 3 & (aux & 0x20) == 0x20){//S5 0010 0000
      *buf++ = '1';
    }else{
      *buf++ = '0';
    }
    //S4->13
    if(count > 4 & (aux & 0x10) == 0x10){//S4 0001 0000
      *buf++ = '1';
    }else{
      *buf++ = '0';
    }
    if(count > 5){
     *buf++ = '\n'; return 5;
    }
    return count;
}

ssize_t practica_write (struct file *filp, const char *buf, size_t count, loff_t *offp){

    if(count < 1){
        return count;
    }
    switch(*buf) {
    case '0' :
      mostrar = 0x3F;//0011 1111 es el 0
      break;
    case '1' :
      mostrar = 0x06;//0000 0110 es el 1
      break;
    case '2' :
      mostrar = 0x5B;
      break;
    case '3' :
      mostrar = 0x4F;
      break;
    case '4' :
      mostrar = 0x66;
      break;
    case '5' :
      mostrar = 0x6D;
      break;
    case '6' :
      mostrar = 0x7D;
      break;
    case '7' :
      mostrar = 0x07;
      break;
    case '8' :
      mostrar = 0x7F;
      break;
    case '9' :
      mostrar = 0x6f;
      break;
    default :
      mostrar = 0x00;
      printk(KERN_WARNING "Caracter invalido\n");
    }
    outb(mostrar,PUERTO_BASE);
    return 1;
}

struct file_operations practica_fops = {
 .read= practica_read,
 .write= practica_write,
 .open= practica_open,
 .release= practica_release,
};

static int prac_init(void)
{
  if (request_region(PUERTO_BASE, RANGO, device_name) == NULL)
	   printk(KERN_INFO "Fallo en el registro de la direccion del dispositivo\n");

  mayor = register_chrdev(MAYOR_NUMBER, device_name, &practica_fops);

  if (mayor < 0) {
    printk(KERN_ALERT "Fallo en el registro del MAYOR_NUMBERe %d\n", mayor);
    return mayor;
  }
  printk(KERN_INFO "Modulo cargado correctamente\n");
  return 0;
}

static void prac_exit(void)
{
  unregister_chrdev(MAYOR_NUMBER, device_name);
	release_region(PUERTO_BASE, RANGO);
  printk(KERN_INFO "Modulo desconectado correctamente\n");
}

module_init(prac_init);
module_exit(prac_exit);
