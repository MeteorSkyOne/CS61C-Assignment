/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include "imageloader.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Opens a .ppm P3 image file, and constructs an Image object.
// You may find the function fscanf useful.
// Make sure that you close the file with fclose before returning.
Image *readData(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "open file err");
        return NULL;
    }
    Image *img = malloc(sizeof(Image));
    if (img == NULL) {
        fprintf(stderr, "malloc err");
        fclose(fp);
        return NULL;
    }
    char buf[20];
    fscanf(fp, "%s", buf);
    if (strcmp("P3", buf) != 0) {
        fprintf(stderr, "Wrong file format");
        free(img);
        fclose(fp);
        return NULL;
    }
    fscanf(fp, "%u %u", &img->cols, &img->rows);
    uint8_t range;
    fscanf(fp, "%hhu", &range);
    img->image = malloc(img->rows * sizeof(Color *));
    if (img->image == NULL) {
        fprintf(stderr, "malloc err for rows");
        free(img);
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < img->rows; i++) {
        img->image[i] = malloc(img->cols * sizeof(Color));
        if (img->image[i] == NULL) {
            fprintf(stderr, "malloc err for row %d", i);
            for (int k = 0; k < i; k++) {
                free(img->image[k]);
            }
            free(img->image);
            free(img);
            fclose(fp);
            return NULL;
        }
        for (int j = 0; j < img->cols; j++) {
            fscanf(fp, "%hhu %hhu %hhu", &img->image[i][j].R,
                   &img->image[i][j].G, &img->image[i][j].B);
        }
    }
    fclose(fp);
    return img;
}

// Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the
// image's data.
void writeData(Image *image) {
    printf("P3\n%u %u\n255\n", image->cols, image->rows);
    for (int i = 0; i < image->rows; i++) {
        for (int j = 0; j < image->cols; j++) {
            printf("%3hhu %3hhu %3hhu", image->image[i][j].R,
                   image->image[i][j].G, image->image[i][j].B);
            if (j != (image->cols - 1)) {
                printf("   ");
            }
        }
        printf("\n");
    }
}

// Frees an image
void freeImage(Image *image) {
    if (image == NULL) return;

    for (int i = 0; i < image->rows; i++) {
        free(image->image[i]);
    }
    free(image->image);
    free(image);
}
