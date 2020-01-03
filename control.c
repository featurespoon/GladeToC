#include <gtk/gtk.h>
#include "top_window.h"
#include "top_window_gui.h"
#include "file_choose2_gui.h"
#include "file_choose1_gui.h"
#include "g2c_message.h"
#include <string.h>
#include <errno.h>

#define FILEBUF 1024

static gchar *filename_s = NULL;
static gchar *foldername_s = NULL;
static gchar *progname_s = NULL;
static gchar *resourcename_s = NULL;


void listfile(GtkTextBuffer* textbuffer, gchar *file);

void initialise_top_window (TopWindowGui *top_window)
{
    return;
}

void messagebox (char *message, char *param, GtkWindow *window1)
{
    	GtkDialogFlags dialogueflags = GTK_DIALOG_DESTROY_WITH_PARENT;
    	GtkWidget  *dialog = gtk_message_dialog_new (window1,
                                 dialogueflags,
                                 GTK_MESSAGE_INFO,
                                 GTK_BUTTONS_CLOSE,
                                 message, param
                                 );
        gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}

void
glade_click (GtkButton* widget,
	gpointer                  user_data)

{
guint response;
GtkWidget *dialog;
gchar *filename = NULL;

	TopWindow *prog = (TopWindow*) g_object_get_data (G_OBJECT (widget), "owner"); 
	dialog = (GtkWidget *) prog->file_choose1gui->file_choose1;
	gtk_widget_show (dialog);
	response = gtk_dialog_run (GTK_DIALOG(dialog));
	
	if (response ==  5) {   // GTK_RESPONSE_ACCEPT but response 5 set in Glade
		
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		filename = gtk_file_chooser_get_filename (chooser);
		filename = g_strdelimit(filename, "\\", '/');
		if (filename == NULL) {
			g_print("No file selected\n");
		} else {
			gtk_entry_set_text(prog->gui->glade_file, filename);
		}
	}
	gtk_widget_hide (dialog);
	return;
}

void
folder_click (GtkButton* widget,
	gpointer                  user_data)

{
guint response;
GtkWidget *dialog;
gchar *foldername = NULL;
gchar *uri = NULL;
gchar *filepos= NULL;
gchar disc[6];
gchar *progname = NULL;

	TopWindow *prog = (TopWindow*) g_object_get_data (G_OBJECT (widget), "owner"); 
	dialog = (GtkWidget *) prog->file_choose2gui->file_choose2;
	gtk_widget_show (dialog);
	response = gtk_dialog_run (GTK_DIALOG(dialog));
	
	if (response ==  5) {   
		
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		uri = gtk_file_chooser_get_uri (chooser);
		uri = g_strdelimit(uri, "\\", '/');
#ifdef WIN32
		filepos = g_strrstr(uri, ":/");
		if (filepos != NULL) {
			disc[0] = (filepos-1)[0];
			disc[1] = 0;
			foldername = g_strdup_printf("%s:/%s", disc, filepos+2);		
		}
#else
		filepos = g_strrstr(uri, "//");		
		if (filepos != NULL) {
			foldername = g_strdup(filepos+1);	
		} 
#endif		 
		if (foldername == NULL) {
			g_print("No folder selected\n");
		} else {
			gtk_entry_set_text(prog->gui->folder, foldername);
			progname = (gchar *) gtk_entry_get_text(prog->gui->program);
			if ((progname == NULL) || (strcmp(progname,"") == 0)) {
				filepos = g_strrstr(foldername, "/");
				if (filepos != 0) {  /*  set default program name from folder name  */
					gtk_entry_set_text(prog->gui->program, filepos+1);
				}
			}			
			g_free (uri);
		}
	}
	gtk_widget_hide (dialog);
	return;
}

void
resource_click (GtkButton* resource_button,
	gpointer                  user_data)
{
guint response;
GtkWidget *dialog;
gchar *rawresource = NULL;
gchar *resourcename = NULL;
gchar *pos;

	g_print("%s clicked\n", "resource file chooser");
#ifdef WIN32	
	TopWindow *prog = (TopWindow*) g_object_get_data (G_OBJECT (resource_button), "owner"); 
	dialog = (GtkWidget *) prog->file_choose3gui->file_choose3;
	gtk_widget_show (dialog);
	response = gtk_dialog_run (GTK_DIALOG(dialog));
	
	g_print("response is %d  \n", response);
	if (response ==  9) {   // GTK_RESPONSE_ACCEPT but response 9 set in Glade
		
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		rawresource = gtk_file_chooser_get_filename (chooser);
		rawresource = g_strdelimit(rawresource, "\\", '/');
		pos = g_strrstr(rawresource, "/");		
		if (pos != NULL) {
			resourcename = g_strdup(pos+1);
		} else {
			resourcename = g_strdup(rawresource);
		}
		if (resourcename == NULL) {
			g_print("No file selected\n");
		} else {
			gtk_entry_set_text(prog->gui->resource, resourcename);			
		}
	}
	gtk_widget_hide (dialog);
#endif	
	return;
}	

void
generate_click (GtkButton* widget,
	gpointer                  user_data)

{
gchar *filename = NULL;
gchar *foldername = NULL;
gchar *progname = NULL;
gchar *resourcename = NULL;
gboolean gen_cmake = TRUE;

	TopWindow *prog = (TopWindow*) g_object_get_data (G_OBJECT (widget), "owner");	
        filename = (gchar *) gtk_entry_get_text(prog->gui->glade_file);
	if (filename == NULL) {
		messagebox("You need to select a glade file", "g2c-3", prog->gui->top_window);
		return;
	}
        foldername = (gchar *) gtk_entry_get_text(prog->gui->folder);
	if (foldername == NULL) {
		messagebox("You need to select a folder for the generated code", "g2c-3", prog->gui->top_window);
		return;
	}
	progname = (gchar *) gtk_entry_get_text(prog->gui->program);
	if (strcmp(progname, "") == 0) {
		messagebox("You need to enter a name for the program that is ultimately made", "g2c-3", prog->gui->top_window);
		return;
	}	
        g2c_message_init((gpointer) prog->gui->textbuffer1);
#ifdef WIN32        
        resourcename = g_strdup((gchar *) gtk_entry_get_text(prog->gui->resource));
	if ((resourcename == NULL) || (strcmp(resourcename, "") == 0)) {
	   g_print ("resource file not supplied\n");
           g_free(resourcename);
           resourcename = NULL;
	} else {
	   g_print("resource name: %s\n", resourcename);
	}
#endif	
	filename_s = g_strdup(filename);
	foldername_s = g_strdup(foldername);
	progname_s = g_strdup(progname);
#ifdef WIN32 
	resourcename_s = g_strdup(resourcename);
	g2c_common(progname, filename, foldername, gen_cmake, resourcename);
#else
	g2c_common(progname, filename, foldername, gen_cmake);
#endif	
	gtk_widget_set_sensitive(GTK_WIDGET(prog->gui->generate_button), FALSE);
	return;
}

void
dismiss_click (GtkButton* widget,
	gpointer                  user_data)

{
	TopWindow *prog = (TopWindow*) g_object_get_data (G_OBJECT (widget), "owner"); 
	if (prog == NULL) {
	  g_print("can't dismiss: owner is NULL\n");
	} else {
	  //top_window_terminate(prog);
	  gtk_main_quit();
	};
	return;
}

	/*  Signal handlers for Dialogue file-choose2 */
void
choose2_click (GtkButton* widget,
	gpointer                  user_data)

{
	/* TopWindow *prog = (TopWindow*) g_object_get_data (G_OBJECT (widget), "owner"); */
	//g_print("%s clicked\n", "choose2");
	return;
}

	/*  Signal handlers for Dialogue file-choose1 */
void
choose1_click (GtkButton* widget,
	gpointer                  user_data)

{
	/* TopWindow *prog = (TopWindow*) g_object_get_data (G_OBJECT (widget), "owner"); */
	//g_print("%s clicked\n", "choose1");
	return;
}

void
choose3_clicked (GtkButton* choose3,
	gpointer                  user_data)
{
	g_print("%s clicked\n", "choose3");
	return;
}	

void listfile(GtkTextBuffer* textbuffer, gchar *file) {  /*   prog->gui->textbuffer1  */
FILE   *gen_file = NULL;
char* errind = NULL;
gchar gentext[FILEBUF];
GtkTextIter iter;
guint count = 0;

	if (file == NULL) return;
	if ((gen_file = fopen(file,"r")) == 0 )  /* open file */
	{
		g_print("Error: cannot find file %s    %s\n", file, strerror(errno));       /* unsuccessful */
		return;
	}
	errind =  fgets(gentext, FILEBUF, gen_file);
	while (errind != NULL) {
		gtk_text_buffer_get_end_iter(textbuffer, &iter);
		gtk_text_buffer_insert(textbuffer, &iter, gentext, -1);	
		count++;		
		errind =  fgets(gentext, FILEBUF, gen_file);		
	}
	fclose(gen_file);
	g_print (" file %s output, count  = %d\n", file, count);
}

