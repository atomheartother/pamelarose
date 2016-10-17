/*
** cryptsetup.h for  in /home/navenn_t/Programmation/crypto/pamelarose
** 
** Made by Thomas Navennec
** Login   <navenn_t@epitech.net>
** 
** Started on  Mon Oct 17 15:16:02 2016 Thomas Navennec
** Last update Mon Oct 17 18:24:25 2016 Thomas Navennec
*/

#ifndef CRYPTSETUP_H_
# define CRYPTSETUP_H_

# define ERR_CRINIT	"Could not init libcryptsetup"
# define ERR_CRFORM	"Could not format file"
# define ERR_KSLOT	"Could not create keyslot"
# define ERR_CRLOAD	"Could not load LUKS header, file may be corrupted"
# define ERR_CRACT	"Could not activate LUKS container"
# define ERR_DEACT	"Failed to deactivate device"
# define CR_HASH	"sha1"
# define CR_CIPHER	"aes"
# define CR_KEY		256 /* in bits */
# define CR_BLOCKMODE	"xts-plain64"

int	format_file(const char * file, int flags);
int	activate_file(const char * file, const char * name, int flags);
int	deactivate_file(const char * name, int flags);

#endif
