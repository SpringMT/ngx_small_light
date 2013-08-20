/**
   Copyright (c) 2013 Tatsuhiko Kubo <cubicdaiya@gmail.com>

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
 */

#include "ngx_http_small_light_module.h"
#include "ngx_http_small_light_type.h"

//
// this original function is brought from nginx/src/http/modules/ngx_http_image_filter_module.c
//
ngx_uint_t ngx_http_small_light_type(u_char *image, size_t image_len)
{
    u_char  *p;

    p = image;

    if (image_len < 16) {
        return NGX_HTTP_SMALL_LIGHT_IMAGE_NONE;
    }

    if (p[0] == 0xff && p[1] == 0xd8) {
        return NGX_HTTP_SMALL_LIGHT_IMAGE_JPEG;

    } else if (p[0] == 'G' && p[1] == 'I' && p[2] == 'F' && p[3] == '8' && p[5] == 'a') {
        if (p[4] == '9' || p[4] == '7') {
            return NGX_HTTP_SMALL_LIGHT_IMAGE_GIF;
        }
    } else if (p[0] == 0x89 && p[1] == 'P'  && p[2] == 'N'  && p[3] == 'G' &&
               p[4] == 0x0d && p[5] == 0x0a && p[6] == 0x1a && p[7] == 0x0a)
    {
        return NGX_HTTP_SMALL_LIGHT_IMAGE_PNG;
    }

    return NGX_HTTP_SMALL_LIGHT_IMAGE_NONE;
}