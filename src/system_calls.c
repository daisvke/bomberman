#include "../so_long.h"

// include in libft
void    ft_free(void *ptr)
{
    if (ptr)
        free(ptr);
}
