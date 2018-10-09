//
// Created by zhanghailong on 2018/10/8.
//


#include "kk-config.h"
#include "kk-dispatch.h"
#include "kk-string.h"
#include "CGContext.h"

namespace kk {

    namespace CG {

        OSImage::OSImage(kk::CString src,kk::CString basePath)
                :_src(src),_basePath(basePath)
        {

        }

        OSImage::~OSImage() {

        }

        Uint OSImage::width() {
            return 0;
        }

        Uint OSImage::height() {
            return 0;
        }


        Boolean OSImage::isCopyPixels() {
            return false;
        }

        void OSImage::copyPixels(void * data) {


        }

        void OSImage::load(OSImage * image) {

            if(kk::CStringHasPrefix(image->src(), "http://")
               || kk::CStringHasPrefix(image->src(), "https://")) {

            } else {

                kk::String b = image->basePath();

                if(b == "") {
                    b = "./";
                } else if(!kk::CStringHasSuffix(b.c_str(), "/")) {
                    b.append("/");
                }

                b.append(image->src());

            }

        }

    }

}

