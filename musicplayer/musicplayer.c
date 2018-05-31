
#include <string.h>
#include <ao/ao.h>
#include <mpg123.h>

#define BITS 8

//initialize variables
mpg123_handle *mh;
unsigned char *buffer;
size_t buffer_size, done;
int err, driver, channels, encoding;
ao_device *dev;
ao_sample_format format;
long rate;


void stop() {
  FILE *in = popen("echo $(ps -a | grep musicplayer) | tr ':' ' '","r");
  char func[5];
  fgets(func, 5, in);
  pclose(in);
  char* salida = "kill ";
  char dest[10];
  strcat(dest, salida);
  strcat(dest, func);
  system(dest);
}

void play(char *song){

  /* open the file and get the decoding format */
  mpg123_open(mh, song);
  mpg123_getformat(mh, &rate, &channels, &encoding);

  /* set the output format and open the output device */
  format.bits = mpg123_encsize(encoding) * BITS;
  format.rate = rate;
  format.channels = channels;
  format.byte_format = AO_FMT_NATIVE;
  format.matrix = 0;
  dev = ao_open_live(driver, &format, NULL);

  /* decode and play */
  while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
   ao_play(dev, buffer, done);

   /* clean up */
   free(buffer);
   ao_close(dev);
   mpg123_close(mh);
   mpg123_delete(mh);
   mpg123_exit();
   ao_shutdown();
  // stop();
}

int main(int argc, char *argv[]){

  /* initializations */
  ao_initialize();
  driver = ao_default_driver_id();
  mpg123_init();
  mh = mpg123_new(NULL, &err);
  buffer_size = mpg123_outblock(mh);
  buffer = (unsigned char*) malloc(buffer_size * sizeof(unsigned char));

  if(argc < 2 || argc > 2){
    printf("Error, debe indicar bien los argumentos\n");
    exit(0);
  }

  if (strcmp(argv[1], "stop") == 0) {
    stop();
    return(0);
  }

  else{
    play(argv[1]);
  }

  return 0;
}
