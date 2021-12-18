#include <stdlib.h>
#include <stdio.h>

#include "../yyjson/yyjson.h"
#include "task.h"

void deserialise(char * json, Task ** tasks, int * len) {
	yyjson_doc * doc = yyjson_read(json, strlen(json), 0);
	yyjson_val * root = yyjson_doc_get_root(doc);

	yyjson_val * tasks_data = yyjson_obj_get(root, "tasks");
	size_t size = yyjson_arr_size(tasks_data);
	*len = size;

	yyjson_val * val;
	yyjson_arr_iter iter;
	yyjson_arr_iter_init(tasks_data, &iter);

	*tasks = calloc(size, sizeof(Task));
	int ctr = 0;

	while ((val = yyjson_arr_iter_next(&iter))) {
		yyjson_val * name = yyjson_obj_get(val, "name");
		yyjson_val * check = yyjson_obj_get(val, "check");

		const char * tmp_name;
		size_t tmp_len;
		
		tmp_name = yyjson_get_str(name);
		tmp_len  = yyjson_get_len(name);
		
		(*tasks)[ctr].name = calloc(tmp_len + 1, sizeof(char *));
		strncpy((*tasks)[ctr].name, tmp_name, tmp_len);
		(*tasks)[ctr].check = yyjson_get_bool(check);

		ctr = ctr + 1;
	}

	yyjson_doc_free(doc);
}

char * serialise(Task ** tasks, int len) {
	yyjson_mut_doc * doc = yyjson_mut_doc_new(NULL);
	yyjson_mut_val * root = yyjson_mut_obj(doc);

	yyjson_mut_val * array = yyjson_mut_arr(doc);
	yyjson_mut_obj_add_val(doc, root, "tasks", array);

	for (int i = 0; i < len; ++i) {
		yyjson_mut_val * entry = yyjson_mut_arr_add_obj(doc, array);
		yyjson_mut_obj_add_str(doc, entry, "name", (*tasks)[i].name);
		yyjson_mut_obj_add_bool(doc, entry, "check", (*tasks)[i].check);
	}

	yyjson_mut_doc_set_root(doc, root);

	char * json = yyjson_mut_write(doc, YYJSON_WRITE_PRETTY, NULL);

	yyjson_mut_doc_free(doc);

	return json;
}
