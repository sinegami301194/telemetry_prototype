#ifndef JSON_JSON_H_INCLUDED
# define JSON_JSON_H_INCLUDED

#ifdef __GNUC__
//prun suppress -Weffc++ warnings in thirdparty
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#endif //__GNUC__

# include "autolink.h"
# include "value.h"
# include "reader.h"
# include "writer.h"
# include "features.h"

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif //__GNUC__

#endif // JSON_JSON_H_INCLUDED
