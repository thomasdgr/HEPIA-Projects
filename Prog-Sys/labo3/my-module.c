#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Thomas Dagier <thomas.dagier-joncour@etu.hesge.ch>");
MODULE_DESCRIPTION("tp sur les modules");
MODULE_VERSION("1.0");

// données globales
struct cdev c;
static int buff_size = 26;
static char buff[26] = "abcdefghijklmnopqrstuvwxyz";
static dev_t dev;

/* objectifs: nouvelle facon de lire notre périphérique
 * entrées: filp -> descripteur de fichier du périphérique, 
 			buffer -> endroit où stocker la lecture, 
			len -> lonqueur des données à lire, 
			offset -> position actuelle du pointeur de lecture
 * sorties: retourne le nombre de bytes qui ont été lu
 * limites des arguments: on ne peut pas lire plus que la taille du buffer -> 26
 * conditions / effets de bords: repositionne le pointeur du buffer sur 0 si on arrive à la fin
 *                               comportement simplifié du buffer circulaire
 */
static ssize_t device_read(struct file *filp, char __user *buffer, size_t len, loff_t *offset){
	// vérification de la taille des données qui peuvent être lues par rapport à ce qui est demandé
	int read = buff_size - *offset;
	int bytes_read = 0;
	// si l'offset dépasse la taille max, on le replace à 0 (début du buffer)
	if(*offset >= buff_size){
		*offset = 0;
	}
	if(len <= buff_size - *offset){
		read = len;
	}
	// lecture
	if(read){
		bytes_read = read - copy_to_user(buffer, buff + *offset, read);
	}
	// mise à jour de l'offset
	*offset += bytes_read;
	return bytes_read;
}

/* objectifs: nouvelle facon d'écrire sur notre périphérique
 * entrées: filp -> descripteur de fichier du périphérique, 
 			buffer -> contenu à écrire, 
			len -> lonqueur des données à écrire, 
			offset -> position actuelle du pointeur de lecture
 * sorties: retourne le nombre de bytes qui ont été écrit
 * limites des arguments: on ne peut pas écrire plus que la taille du buffer -> 26
 * conditions / effets de bords: repositionne le pointeur du buffer sur 0 si on arrive à la fin
 *                               comportement simplifié du buffer circulaire
 */
static ssize_t device_write(struct file *filp, const char __user *buffer, size_t len, loff_t *offset){
	// le fonctionnement est exactement le même que pour le read()
	int write = buff_size - *offset;
	int bytes_written = 0;
	if(*offset >= buff_size){
		*offset = 0;
	}
	if(len <= buff_size - *offset){
		write = len;
	}
	// ecriture
	if(write){
		bytes_written = write - copy_from_user(buff + *offset, buffer, write);
	}
	*offset += bytes_written;
	return bytes_written;
}

// structure de données qui décrit quelles fonctions utiliser en cas
// de read() / write() sur notre fichier de périphérique 
static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
};

// partie initialisation et exit reprise du cours

static int __init mod_init(void){
	int val;
	val = alloc_chrdev_region(&dev, 0, 1, "abcd");
	if(val < 0){
		printk(KERN_ERR "Error with the major during the register\n");
		return val;
	}
	cdev_init(&c, &fops);
	val = cdev_add(&c, dev, 1);
	if(val != 0){
		printk(KERN_ERR "Error with cdev_add");
		return val;
	}
	return 0;
}

static void __exit mod_exit(void){
	cdev_del(&c);
	unregister_chrdev(dev, "abcd");
}

module_init(mod_init);
module_exit(mod_exit);