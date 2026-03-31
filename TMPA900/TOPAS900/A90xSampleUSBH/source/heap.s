;;; Copyright ARM Ltd 2001. All rights reserved.

        AREA    Heap, DATA, NOINIT

        EXPORT top_of_heap

; Create dummy variable used to locate bottom of heap

top_of_heap    SPACE   0x0800                        ; 2KB size for Heap

        END
