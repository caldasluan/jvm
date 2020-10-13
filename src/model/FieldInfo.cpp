
#include <stdio.h>
#include "FieldInfo.h"
#include "AttributeInfo.h"
#include "../constants/AcessFlagsFieldConst.h"
#include "../constants/AcessFlagsClassConst.h"
#include <cstdint>
#include <vector>
#include <memory>



void showFields(field_info *fields, unit16_t fields_count){
	int i,j;

	for(i=0; i<fields_count; i++){

	switch(fields->access_flags){
		case(PUBLIC):
			printf("\tFields - Access Flags: Public\n");
			break;
		case(PRIVATE):
			printf("\tFields - Access Flags: Private\n");
			break;
		case(PROTECTED):
			printf("\tFields - Access Flags: Protected\n");
			break;
		case(STATIC):
			printf("\tFields - Access Flags: Static\n");
			break;
		case(FINAL):
			printf("\tFields - Access Flags: Final\n");
			break;
		case(VOLATILE):
			printf("\tFields - Access Flags: Volatile\n");
			break;
		case(TRANSCIENT):
			printf("\tFields - Access Flags: Transcient\n");
			break;
		case(ENUM):
			printf("\tFields - Access Flags: Enum\n");
			break;
	}
	printf("\tFields - Name Index: %02x\n", fields->name_index);
	printf("\tFields - Descriptor Index: %02x\n", fields->descriptor_index);
	printf("\tFields - Attributes Count: %02x\n", fields->attributes_count);



	}
}
