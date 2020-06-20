#include <glib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <gtk/gtk.h>
#include "g2c_message.h"

/*  The COMMAND interface  */

/* Does the file exist? */
gboolean check_exists (gchar * file)
{
struct stat s_stat;    

  if( -1 == stat( file, &s_stat ) ) {
      if( ENOENT == errno )  {
          g_print( "\n*** ERROR ***: File %s does not exist.\n\n", file );
          return FALSE;
      }  else {
          g_error( "Probable access error on file %s.\n", file );
      }     
  }
  return TRUE;
}

int usage(char *prog) {
#ifdef WIN32
  g_print("Usage: %s [-p name] -g gladefile -d dir [-r resource] [-x] [-h]\n", prog);
#else
  g_print("Usage: %s [-p name] -g gladefile -d dir [-h]\n", prog);
#endif  
  g_print("\t-p\t- Project (program) name.\n");
  g_print("\t-g\t- file produced by GLADE.\n");
  g_print("\t-d\t- directory into which generated files are placed.\n");
  g_print("\t-x\t- do not produce CMAKE file.\n");
#ifdef WIN32  
  g_print("\t-r\t- Resource file.\n");
#endif 
  g_print("\t-n\t- No check for new handlers.\n");
  g_print("\t-h\t- Help. This message.\n");
  return 0;
}

int main( int argc, char *argv[] )
{
char   *prog_name = argv[0];
char    c;
char   *glade_file = NULL;  /* The filename of the glade file */
char   *gen_dir    = NULL;  /* The directory into which the generated files are put */
char   *program    = NULL;
char   *resource_file = NULL;
gboolean gen_cmake = TRUE;
gboolean no_parsing = FALSE;
int ret;

gchar wdir[PATH_MAX];

// command-line option handling 
#ifdef WIN32
   while ((c = getopt(argc, argv, "g:d:p:xnr:h"))!= -1) {
#else
   while ((c = getopt(argc, argv, "g:d:p:h"))!= -1) {
#endif       
        switch (c) {
            case 'p':
                program = g_strdup(optarg);
                break;
	    case 'g':
                glade_file = g_strdup(optarg);
                break;
            case 'd':
                gen_dir = g_strdup(optarg);
                break;
            case 'x':
                gen_cmake = FALSE;
                break;
            case 'n':
                no_parsing = TRUE;
                break;
#ifdef WIN32                
            case 'r':
                resource_file =  g_strdup(optarg);
                break;
#endif                
            default:
	      usage(prog_name);
	      return 1;
	      break;
	 }
   }
   
  g2c_message_init((gpointer) NULL);

  if ( glade_file == NULL ) {
      g_message ("Please provide a .glade file to process (option -g)\n");
      usage(prog_name);
      return 1;
   }
      
  if ( gen_dir == NULL ) {
      //gen_dir = g_strdup_printf("%s/gen", getcwd(wdir, PATH_MAX));
      //g_print ("Directory for the generated files: %s\n", gen_dir); 
      g_message("No option -d found. Please supply a directory for the generated code.\n");
      return 1;
  }
  //   g_type_init_with_debug_flags() is no longer supported.  Use the GOBJECT_DEBUG environment variable.
  gtk_init (&argc, &argv);    
  
  if (!check_exists ( glade_file )) return 1;
  
#ifdef WIN32  
  ret = g2c_common(program, 
          glade_file, 
          gen_dir, 
          gen_cmake, 
          no_parsing, 
          resource_file);
#else
  ret = g2c_common(program, 
          glade_file, 
          gen_dir, 
          gen_cmake, 
          no_parsing);
#endif
  
  return ret;
}
