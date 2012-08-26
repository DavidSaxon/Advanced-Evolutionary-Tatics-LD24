#include "Engine.hpp"

//FUNCTIONS
/*Loads all the textures into memory*/
void Engine::loadTextures() {
    int width, height;
    bool hasAlpha;

    //load background textures
    loadImage((char*) "data/gfx/background/grass.png", width, height, hasAlpha, &backgroundImg);
    glGenTextures(1, &backgroundTex);
    glBindTexture(GL_TEXTURE_2D, backgroundTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, backgroundImg);

    loadImage((char*) "data/gfx/background/rock.png", width, height, hasAlpha, &rockImg);
    glGenTextures(1, &rockTex);
    glBindTexture(GL_TEXTURE_2D, rockTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rockImg);

    //load attack textures
    loadImage((char*) "data/gfx/attack/attackSmall.png", width, height, hasAlpha, &attackSmallImg);
    glGenTextures(1, &attackSmallTex);
    glBindTexture(GL_TEXTURE_2D, attackSmallTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, attackSmallImg);

    /*loadImage((char*) "data/gfx/attack/attackMed.png", width, height, hasAlpha, &attackMedImg);
    glGenTextures(1, &attackMedTex);
    glBindTexture(GL_TEXTURE_2D, attackMedTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, attackMedImg);

    loadImage((char*) "data/gfx/attack/attackLarge.png", width, height, hasAlpha, &attackLargeImg);
    glGenTextures(1, &attackLargeTex);
    glBindTexture(GL_TEXTURE_2D, attackLargeTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, attackLargeImg);*/

    //load nexus textures
    loadImage((char*) "data/gfx/nexus/nexus.png", width, height, hasAlpha, &nexusBodyImg);
    glGenTextures(1, &nexusBodyTex);
    glBindTexture(GL_TEXTURE_2D, nexusBodyTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nexusBodyImg);

    loadImage((char*) "data/gfx/nexus/nexusBlue.png", width, height, hasAlpha, &nexusBlueImg);
    glGenTextures(1, &nexusBlueTex);
    glBindTexture(GL_TEXTURE_2D, nexusBlueTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nexusBlueImg);

    loadImage((char*) "data/gfx/nexus/nexusRed.png", width, height, hasAlpha, &nexusRedImg);
    glGenTextures(1, &nexusRedTex);
    glBindTexture(GL_TEXTURE_2D, nexusRedTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nexusRedImg);

    //load unit textures
    loadImage((char*) "data/gfx/unit/softBodySmall.png", width, height, hasAlpha, &softBodySmallImg);
    glGenTextures(1, &softBodySmallTex);
    glBindTexture(GL_TEXTURE_2D, softBodySmallTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, softBodySmallImg);


    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    free(backgroundImg);
    free(rockImg);
    free(attackSmallImg);
    //free(attackMedImg);
    //free(attackLargeImg);
    free(nexusBodyImg);
    free(nexusBlueImg);
    free(nexusRedImg);
    free(softBodySmallImg);
}

/*Loads a png image*/
bool Engine::loadImage(char* name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData) {
    png_structp pngPtr;
    png_infop infoPtr;
    unsigned int sigRead = 0;
    int colorType, interlaceType;
    FILE* file;

    if ((file = fopen(name, "rb")) == NULL) return false;

    pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (pngPtr == NULL) {
        fclose(file);
        return false;
    }

    infoPtr = png_create_info_struct(pngPtr);
    if (infoPtr == NULL) {
        fclose(file);
        png_destroy_read_struct(&pngPtr, png_infopp_NULL, png_infopp_NULL);
        return false;
    }

    if (setjmp(png_jmpbuf(pngPtr))) {
        png_destroy_read_struct(&pngPtr, &infoPtr, png_infopp_NULL);
        fclose(file);
        return false;
    }

    png_init_io(pngPtr, file);
    png_set_sig_bytes(pngPtr, sigRead);

    png_read_png(pngPtr, infoPtr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, png_voidp_NULL);

    outWidth = infoPtr->width;
    outHeight = infoPtr->height;

    switch (infoPtr->color_type) {
        case PNG_COLOR_TYPE_RGBA:
            outHasAlpha = true;
            break;
        case PNG_COLOR_TYPE_RGB:
            outHasAlpha = false;
            break;
        default:
            cout << "Color type " << infoPtr->color_type << " not supported" << endl;
            png_destroy_read_struct(&pngPtr, &infoPtr, NULL);
            fclose(file);
            return false;
    }

    unsigned int rowBytes = png_get_rowbytes(pngPtr, infoPtr);
    *outData = (unsigned char*) malloc(rowBytes*outHeight);
    png_bytepp rowPointers = png_get_rows(pngPtr, infoPtr);

    for (int i = 0; i < outHeight; i++)
        memcpy(*outData+(rowBytes*(outHeight-1-i)), rowPointers[i], rowBytes);

    png_destroy_read_struct(&pngPtr, &infoPtr, png_infopp_NULL);
    fclose(file);

    return true;
}
