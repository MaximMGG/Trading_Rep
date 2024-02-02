


a.out:
	gcc lib/m_string.c lib/m_list.c dc/src/datacenter.c dc/src/dbinsert.c manager/src/app.c service/src/getservice.c -l_util -lcurl -lpq -g
