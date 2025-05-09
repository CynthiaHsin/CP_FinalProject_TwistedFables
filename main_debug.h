# if defined( _DEBUG_ )
    # define debug_print(fmt, ...) fprintf (stderr, "%s : %d : %s(): || " fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__ )
# else 
    # define debug_print(fmt, ...) {}
# endif