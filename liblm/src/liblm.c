#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <hpdf.h>

#include "../include/liblm.h"

void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data);

void format_line(HPDF_Page *page, HPDF_Real xpos, HPDF_Real ypos, char *text);

int lm_compile(char *input_txt, const char *output_fn)
{
    HPDF_Doc pdf;
    HPDF_Page page;
    HPDF_Font font, boldFont, italicFont, monoFont;
    HPDF_REAL xpos = 50, ypos, page_width, page_height, text_width;
    HPDF_REAL font_size = 12, heading_size = 32, subheading_size = 20.8;
    HPDF_REAL lfsize = 12;

    // Initialize the library and set the error handler
    pdf = HPDF_New(error_handler, NULL);
    if (!pdf) {
        printf("ERROR: cannot create PDF object\n");
        return 1;
    }

    // Set up the PDF document
    HPDF_SetCompressionMode(pdf, HPDF_COMP_ALL);
    font = HPDF_GetFont(pdf, "Times-Roman", NULL);
    boldFont = HPDF_GetFont(pdf, "Times-Bold", NULL);
    italicFont = HPDF_GetFont(pdf, "Times-Italic", NULL);
    monoFont = HPDF_GetFont(pdf, "Courier", NULL);

    // Create the first page
    page = HPDF_AddPage(pdf);
    HPDF_Page_SetFontAndSize(page, font, font_size);

    page_width = HPDF_Page_GetWidth(page) - 2 * xpos;
    page_height = HPDF_Page_GetHeight(page);
    ypos = page_height - 50;

    // Iterate over the input text and parse it line by line
    HPDF_Page_BeginText(page);

    char *input_copy = strdup(input_txt);
    char *saveptr_line, *saveptr_word;
    char *line = strtok_r(input_copy, "\n", &saveptr_line);
    int list = 1;
    while (line) {
        char *word = strtok_r(line, " ", &saveptr_word);
        if (word == NULL)
        {
            // Empty line
            continue;
        }
        bool new_line = true;
        // reset font to normal
        HPDF_Page_SetFontAndSize(page, font, font_size);
        HPDF_Page_SetRGBFill(page, 0, 0, 0);

        lfsize = font_size;
        while (word) {
            printf("word: %s\n", word);

            // Wrap words
            text_width = HPDF_Page_TextWidth(page, word);
            if (xpos + text_width > page_width) {
                ypos -= lfsize;
                xpos = 50;

                // Add a new page if needed
                if (ypos < 50) {
                    HPDF_Page_EndText(page);
                    page = HPDF_AddPage(pdf);
                    HPDF_Page_SetFontAndSize(page, font, font_size);
                    ypos = page_height - 50;
                    HPDF_Page_BeginText(page);
                }
            }

            // Add a space if needed
            if (new_line) {
                new_line = false;
            } else {
                HPDF_Page_TextOut(page, xpos, ypos, " ");
                xpos += HPDF_Page_TextWidth(page, " ");
            }

            // Font size heading
            if (strncmp(word, ".h", 2) == 0 && xpos == 50) {
                HPDF_Page_SetFontAndSize(page, font, heading_size);
                lfsize = heading_size;
                word = strtok_r(NULL, " ", &saveptr_word);
                new_line = true;
                continue;
            }
            else if (strncmp(word, ".s", 2) == 0 && xpos == 50) {
                HPDF_Page_SetFontAndSize(page, font, subheading_size);
                lfsize = subheading_size;
                word = strtok_r(NULL, " ", &saveptr_word);
                new_line = true;
                continue;
            }

            // Change font to bold
            if (strncmp(word, ".b", 2) == 0 && xpos == 50) {
                HPDF_Page_SetFontAndSize(page, boldFont, font_size);
                word = strtok_r(NULL, " ", &saveptr_word);
                new_line = true;
                continue;
            }
            // change font to italic
            if (strncmp(word, ".i", 2) == 0 && xpos == 50) {
                HPDF_Page_SetFontAndSize(page, italicFont, font_size);
                word = strtok_r(NULL, " ", &saveptr_word);
                new_line = true;
                continue;
            }
            // add link
            if (strncmp(word, ".a", 2) == 0 && xpos == 50) {
                HPDF_Page_SetRGBFill(page, 0, 0, 1);
                word = strtok_r(NULL, " ", &saveptr_word);
                new_line = true;
                continue;
            }
            // code block
            if (strncmp(word, ".c", 2) == 0 && xpos == 50) 
            {
                HPDF_Page_SetFontAndSize(page, monoFont, font_size);
                word = strtok_r(NULL, " ", &saveptr_word);
                new_line = true;
                continue;
            }
            // block quote grey box around text
            if (strncmp(word, ".q", 2) == 0 && xpos == 50) 
            {
                HPDF_Page_SetRGBFill(page, 0.5, 0.5, 0.5);

                word = strtok_r(NULL, " ", &saveptr_word);
                new_line = true;
                continue;
            }
            // unordered list
            if (strncmp(word, ".l", 2) == 0 && xpos == 50)
            {
                HPDF_Page_TextOut(page, xpos, ypos, "•");
                xpos += HPDF_Page_TextWidth(page, "•");
                word = strtok_r(NULL, " ", &saveptr_word);
                new_line = true;
                continue;
            }
            // ordered list
            if (strncmp(word, ".o", 2) == 0 && xpos == 50)
            {
                char list_num[10];
                sprintf(list_num, "%d. ", list);
                HPDF_Page_TextOut(page, xpos, ypos, list_num);
                xpos += HPDF_Page_TextWidth(page, list_num);
                word = strtok_r(NULL, " ", &saveptr_word);
                new_line = true;
                list++;
                continue;
            }


            // Print the word to page
            HPDF_Page_TextOut(page, xpos, ypos, word);
            // Advance the x position by 1 word
            xpos += text_width + HPDF_Page_TextWidth(page, " ");

            // Get the next word
            word = strtok_r(NULL, " ", &saveptr_word);
        }

        line = strtok_r(NULL, "\n", &saveptr_line);
        ypos -= lfsize;
        xpos = 50;
    }

    HPDF_Page_EndText(page);
    free(input_copy);

    // Save the PDF document to a file and clean up resources
    HPDF_SaveToFile(pdf, output_fn);
    HPDF_Free(pdf);

    return 0;
}

// void format_line(HPDF_Page *page, HPDF_Real xpos, HPDF_Real ypos, char *text)
// {
//     char tag = '\0';
//     char content[MAX_LINE_LEN] = "";

//     sscanf(text, ".%c %7500[^\n]", &tag, content);
//     if (strncmp(tag, "", 2) != 0) {
//         switch (tag)
//         {
//         case 'b':
            
//             break;
        
//         default:
//             break;
//         }
//     }


// }

void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data) {
    printf("ERROR: error_no=%04X, detail_no=%d\n", (unsigned int) error_no, (int) detail_no);
    exit(EXIT_FAILURE);
}