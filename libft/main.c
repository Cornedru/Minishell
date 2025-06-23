/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndehmej <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:37:38 by ndehmej           #+#    #+#             */
/*   Updated: 2024/12/18 01:10:53 by ndehmej          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>


int testoverflow(int x, int y)
{
	return (x * y);
}

int	main(void)
{
	int		a = 42;
	char	*str = "Hello World!";
	char	*str2 = "";
	char	*str3 = NULL;
	void	*ptr1 = (void *)0;
	void	*ptr2 = (void *)&a;
	int		*dynamic_ptr = (int *)malloc(sizeof(int));
	void	*max_ptr  = (void *)-1;
	int		return_value_ft;
	int		return_value_std;
	void	*ptr = NULL;
	int		nb = 2147483647; // int max
	int 	nb2 = -2147483648; // int min 
	unsigned int nbr = 4294967295; // unsigned int max
	unsigned int nbr3 = 0;

	printf("\n--------------------------------------------------------------------------------------------\n");
	printf("\n>>> ON TESTE c (ft_printf puis printf)\n\n");
	ft_printf("Bonjour %c\n", 'e');
	printf("Bonjour %c\n", 'e');
	printf("\n--------------------------------------------------------------------------------------------\n");
	printf("\n>>> ON TESTE s (ft_printf puis printf)\n\n");
	ft_printf("Je dis : %s\n", str);
	printf("Je dis : %s\n", str);
	ft_printf("Bonjour (str vide) : %s\n", str2);
	printf("Bonjour (str vide) : %s\n", str2);
	ft_printf("Bonjour (null) : %s\n", str3);
	printf("Bonjour (null) : %s\n", str3);

	printf("\n--------------------------------------------------------------------------------------------\n");
	printf("\n>>> ON TESTE p (ft_printf puis printf)\n\n");
	ft_printf("Null : %p\n", ptr);
	printf("Null : %p\n", ptr);
	ft_printf("Variable : %p\n", &a);
	printf("Variable : %p\n", &a);
	ft_printf("Str : %p\n", str);
	printf("Str : %p\n", str);
	ft_printf("0x0 : %p\n", ptr1);
	printf("0x0 : %p\n", ptr1);
	ft_printf("Pointeur void valide : %p\n", ptr2);
	printf("Pointeur void valide : %p\n", ptr2);
	ft_printf("Pointeur alloue dynamiquement : %p\n", dynamic_ptr);
	printf("Pointeur alloue dynamiquement : %p\n", dynamic_ptr);
	ft_printf("Valeur max pour un pointeur : %p\n", max_ptr);
	printf("Valeur max pour un pointeur : %p\n", max_ptr);
	ft_printf("Plusieurs pointeurs : %p, %p\n", &a, (void *)0);
	printf("Plusieurs pointeurs : %p, %p\n", &a, (void *)0);

	printf("\n--------------------------------------------------------------------------------------------\n");
	printf("\n>>> ON TESTE d (ft_printf puis printf)\n\n");
	ft_printf("Nb positif : %d\n", 42);
	printf("Nb positif : %d\n", 42);
	ft_printf("Nb negatif : %d\n", -42);
	printf("Nb negatif : %d\n", -42);
	ft_printf("26 en hex : %d\n", 0x1A);
	printf("26 en hex : %d\n", 0x1A);
	ft_printf("Int min : %d\n", nb2);
	printf("Int min : %d\n", nb2);
	ft_printf("Int max : %d\n", nb);
	printf("Int max : %d\n", nb);
	ft_printf("Unsigned int 0 : %d\n", nbr3);
	printf("Unsigned int 0 : %d\n", nbr3);
	ft_printf("TEST: %d\n", UINT_MAX + 1);
	printf("TEST: %d\n", UINT_MAX + 1);
	ft_printf("TEST: %d\n", UINT_MAX * -1);
	printf("TEST: %d\n", UINT_MAX * -1);

	printf("\n--------------------------------------------------------------------------------------------\n");
	printf("\n>>> ON TESTE i (ft_printf puis printf)\n\n");
	ft_printf("Nb positif : %i\n", 42);
	printf("Nb positif : %i\n", 42);
	ft_printf("Nb negatif : %i\n", -42);
	printf("Nb negatif : %i\n", -42);
	ft_printf("26 en hex : %i\n", 0x1A);
	printf("26 en hex : %i\n", 0x1A);
	ft_printf("Int min : %i\n", nb2);
	printf("Int min : %i\n", nb2);
	ft_printf("Int max : %i\n", nb);
	printf("Int max : %i\n", nb);
	ft_printf("Unsigned int 0 : %i\n", nbr3);
	printf("Unsigned int 0 : %i\n", nbr3);

	printf("\n--------------------------------------------------------------------------------------------\n");
	printf("\n>>> ON TESTE u (ft_printf puis printf)\n\n");
	ft_printf("Nb positif : %u\n", 42);
	printf("Nb positif : %u\n", 42);
	ft_printf("Nb negatif : %u\n", -42);
	printf("Nb negatif : %u\n", -42);
	ft_printf("26 en hex : %u\n", 0x1A);
	printf("26 en hex : %u\n", 0x1A);
	ft_printf("Int min : %u\n", nb2);
	printf("Int min : %u\n", nb2);
	ft_printf("Int max : %u\n", nb);
	printf("Int max : %u\n", nb);
	ft_printf("Unsigned int 0 : %u\n", nbr3);
	printf("Unsigned int 0 : %u\n", nbr3);
	
	printf("\n--------------------------------------------------------------------------------------------\n");
	printf("\n>>> ON TESTE x minuscule (ft_printf puis printf)\n\n");
	ft_printf("255, devient ff : %x\n", 255);
	printf("255, devient ff : %x\n", 255);
	ft_printf("Zero, devient 0 : %x\n", 0);
	printf("Zero, devient 0 : %x\n", 0);
	ft_printf("Unsigned int max 4294967295, devient ffffffff : %x\n", nbr);
	printf("Unsigned int max 4294967295, devient ffffffff : %x\n", nbr);
	ft_printf("16, devient 10 : %x\n", 16);
	printf("16, devient 10 : %x\n", 16);
	ft_printf("42, devient 2a : %x\n", 42);
	printf("42, devient 2a : %x\n", 42);
	ft_printf("-42, devient ffffffd6 : %x\n", -42);
	printf("-42, devient ffffffd6 : %x\n", -42);
	
	printf("\n--------------------------------------------------------------------------------------------\n");
	printf("\n>>> ON TESTE X majuscule (ft_printf puis printf)\n\n");
	ft_printf("255, devient FF : %X\n", 255);
	printf("255, devient FF : %X\n", 255);
	ft_printf("Zero, devient 0 : %X\n", 0);
	printf("Zero, devient 0 : %X\n", 0);
	ft_printf("Unsigned int max 4294967295, devient FFFFFFFF : %X\n", nbr);
	printf("Unsigned int max 4294967295, devient FFFFFFFF : %X\n", nbr);
	ft_printf("16, devient 10 : %X\n", 16);
	printf("16, devient 10 : %X\n", 16);
	ft_printf("42, devient 2A : %X\n", 42);
	printf("42, devient 2A : %X\n", 42);
	ft_printf("42, devient FFFFFFD6 : %X\n", -42);
	printf("42, devient FFFFFFD6 : %X\n", -42);
	ft_printf("TEST: %X\n", UINT_MAX * -1);
	printf("TEST: %X\n", UINT_MAX * -1);

	printf("\n--------------------------------------------------------------------------------------------\n");
	printf("\n>>> ON TESTE %% (ft_printf puis printf)\n\n");
	ft_printf("%%\n");
	printf("%%\n");
	ft_printf("ft_printf %%%%%%\n");
	printf("printf %%%%%%\n");

	printf("\n--------------------------------------------------------------------------------------------\n");
	printf("\n>>> ON TESTE plusieurs specificateurs a la fois (ft_printf puis printf)\n\n");
	ft_printf("Char %c, chaine %s, ptr void %p, decimal %d, entier %i, decimal non signe %u, hex minuscule %x, hex majuscule %X et signe pourcent %%\n", 'e', "Elodie", str, 42, 42, 42, 42, 42);
	printf("Char %c, chaine %s, ptr void %p, decimal %d, entier %i, decimal non signe %u, hex minuscule %x, hex majuscule %X et signe pourcent %%\n", 'e', "Elodie", str, 42, 42, 42, 42, 42);

	printf("\n--------------------------------------------------------------------------------------------\n");
	printf("\n>>> ON TESTE avec overflow (ft_printf puis printf)\n\n");
	ft_printf("On multiplie 2147483647 * 21500 (comportement indefini) : %d\n", testoverflow(2147483647, 21500));
	printf("On multiplie 2147483647 * 21500 (comportement indefini): %d\n", testoverflow(2147483647, 21500));

	printf("\n--------------------------------------------------------------------------------------------\n");
	printf("\n>>> ON VERIFIE que les valeurs de retour sont identiques (ft_printf puis printf)\n\n");
	printf("--- Test simple ---\n");
	return_value_ft = ft_printf("Hello world\n");
	printf("ft_printf renvoie: %d\n", return_value_ft);
	return_value_std = printf("Hello world\n");
	printf("printf renvoie: %d\n", return_value_std);
	printf("\n--- Test avec des conversions ---\n");
	return_value_ft = ft_printf("Nombre : %d, Hex: %x\n", 42, 42);
	printf("ft_printf renvoie: %d\n", return_value_ft);
	return_value_std = printf("Nombre : %d, Hex: %x\n", 42, 42);
	printf("printf renvoie: %d\n", return_value_std);

	// La vraie segfault, la mienne non => c'est le comportement attendu
	//ft_printf("ft_printf %d\n", ft_printf(""));
	//printf("printf %d\n", printf(""));

	free(dynamic_ptr);
	return (0);
}
