OUTPUT_FORMAT("binary")
OUTPUT_ARCH("i386:x86-64")
ENTRY(main)
SECTIONS
{
	. = 0x0000000000200000;
	.text : {
                . = ALIGN(16);
		*(.text)
                . = ALIGN(4);
                *(.init)
                . = ALIGN(4);
                *(.fini)
	}
	.data : {
                . = ALIGN(8);
                __init_array_start = .;
                *(.init_array) 
                __init_array_end = .;
                . = ALIGN(8);
                *(.fini_array)
                . = ALIGN(8);
		*(.data)
                . = ALIGN(32);
		*(.rodata)
	}
	.bss : {
		. = ALIGN(32);
                __bss_start = .;
		bss = .; _bss = .; __bss = .;
		*(.bss);
	}
	end = .; _end = .; __end = .;
}
