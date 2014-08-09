/***********************************************************************

   getline.c -- Get a specific line of a file
   Copyright (C) 2014 DIban Hakistron.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main (int argc, char *argv[])
{
  FILE *file = stdin;
  long int line_number;
  long int number_of_lines = 0;
  char ch;
  char *line = NULL; /* Always initialize a pointer */
  const size_t size = 1024;
  char *endptr, *str;
  
  /* Count from one flag */
  int count_from_one_flag = 0;

  if (argc < 2)
    {
      fprintf (stderr, "Usage: %s [-1] LINENUMBER [FILE]\n -1: Count from 1, instead of 0", argv[0]);
      exit (EXIT_FAILURE);
    }
  
  line = malloc (sizeof (char) * size);
  memset (line, 0, size);

  if (argv[1][0] == '-')
    {
      if (argv[1][1] == '1')
	{
	  count_from_one_flag = 1;
	  --argc;
	  ++argv;
	}
      else
	{
	  fprintf (stderr, "Usage: %s [-1] LINENUMBER [FILE]\n -1: Count from 1, instead of 0", argv[0]);
	  free (line);
	  exit (EXIT_FAILURE);
	}
    }

  str = *++argv;
  --argc;
  line_number = strtol (str, &endptr, 10);
  if (endptr == str) /* If no digit was found */
    {
      fprintf (stderr, "First argument isn't a number\n");
      free (line);
      exit (EXIT_FAILURE);
    }
  
  if (count_from_one_flag == 1)
    line_number--;

  if (--argc > 0)
    {
      file = fopen (*++argv, "r");
      if (file == NULL) /* If file could not be openened */
	{
	  perror ("Error while opening file");
	  free (line);
	  exit (EXIT_FAILURE);
	}
    }
  
  while (number_of_lines < line_number) /* Go through file till line */
    {
      ch = getc (file);
      
      if (ch == '\n')
	number_of_lines++;
      else if (ch == EOF)
	{
	  fprintf (stderr, "End of file\n");
	  free (line);
	  exit (EXIT_FAILURE);
	}
    }
  
  fgets (line, size, file); /* Read line in buffer *line */
  if (line == NULL)
    {
      fprintf (stderr, "Error in getline\n");
      free (line);
      exit (EXIT_FAILURE);
    }

  printf (line); /* Print line */

  free (line);

  return EXIT_SUCCESS;
}
