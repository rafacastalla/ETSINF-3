#include<linux/module.h>
#include<linux/kernel.h>
#include <linux/proc_fs.h>
#include<linux/sched.h>

//task_pid_nr(proces)
//pid_t    pid
asmlinkage long sys_generacion(int pid){
    if(pid)	printk("[sys_generacion]Posicion del arbol del pid: %ld\n ",pid);
      struct task_struct *proces;
      struct task_struct *mi_process=0;
      int cont=0;int en=0;

      for_each_process(proces) {
	if((int)proces->pid == pid){
	    mi_process=proces;
	    en=1;
	}
      }
   if(en==0){
      printk("[sys_generacion] Sin proces padres");
      return -ESRCH;
    }
    if(!mi_process){
      printk("[sys_generacion] Sin proces padres");
      return -ESRCH;
    }
    while((int)mi_process->pid!=1){
      cont++;
      if(mi_process->parent)
      mi_process=mi_process->parent;
      else {
        printk("Error no parent");
        return -ESRCH;
      }
    }
     printk("[sys_generacion]Total de papis: %ld\n ",cont);
     printk("[sys_generacion]Posicion Tree: %ld\n ",cont+1);
return cont+1;
}