


a.out:
	gcc main.c core/candle/src/candleformatting.c db/src/dbinsert.c logic/src/app.c logic/src/realtimework.c service/src/getservice.c -l_util -lcurl -lpq -g
