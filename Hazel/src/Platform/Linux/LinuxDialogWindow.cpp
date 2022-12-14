#include "hzpch.h"
#include "Platform/Linux/LinuxDialogWindow.h"

namespace Hazel {

  LinuxDialogWindow::LinuxDialogWindow(void)
  {
    set_title("Hazel Scene File Selector");
    signal_show().connect(sigc::mem_fun(*this, &LinuxDialogWindow::OnFileButtonClicked));
  }

  LinuxDialogWindow::~LinuxDialogWindow(void)
  {
  }

  void LinuxDialogWindow::SubmitHazelFilter(const char* filter)
  {
    int i = 0;
    while (filter[i] != '\0') {
      m_HZFilterName += filter[i];
      i++;
    } // while (filter[i] != '\0') {

    HZ_CORE_TRACE("m_HZFilterName = '{0}'", m_HZFilterName);

    i++; // Skip \0 character
    while (filter[i] != '\0') {
      m_HZFilterPattern += filter[i];
      i++;
    } // while (filter[i] != '\0') {

    HZ_CORE_TRACE("m_HZFilterPattern = '{0}'", m_HZFilterPattern);

    return;
  }

  void LinuxDialogWindow::OnFileButtonClicked(void)
  {
    Gtk::FileChooserDialog dialog("Please choose a scene", Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    // Add response buttons to the dialog
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

    // Add filters, so that only certain file types can be selected:

    Glib::RefPtr<Gtk::FileFilter> filterHazel = Gtk::FileFilter::create();
    filterHazel->set_name(m_HZFilterName);
    filterHazel->add_pattern(m_HZFilterPattern);
    dialog.add_filter(filterHazel);

    Glib::RefPtr<Gtk::FileFilter> filter_text = Gtk::FileFilter::create();
    filter_text->set_name("Text files");
    filter_text->add_mime_type("text/plain");
    dialog.add_filter(filter_text);

    Glib::RefPtr<Gtk::FileFilter> filter_cpp = Gtk::FileFilter::create();
    filter_cpp->set_name("C/C++ files");
    filter_cpp->add_mime_type("text/x-c");
    filter_cpp->add_mime_type("text/x-c++");
    filter_cpp->add_mime_type("text/x-c-header");
    filter_cpp->add_mime_type("text/x-c++-header");
    dialog.add_filter(filter_cpp);

    Glib::RefPtr<Gtk::FileFilter> filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);

    // Show the dialog and wait for a user response:
    int result = dialog.run();

    // Handle the response:
    switch (result) {
    case Gtk::RESPONSE_OK:
    {
      // Notice this is a std::string, not a Glib::ustring.
      m_ChosenFile = dialog.get_filename();
      break;
    }
    case Gtk::RESPONSE_CANCEL:
    {
      break;
    }
    default:
    {
      break;
    }
    } // switch (result) {

    close();

    return;
  }

}
