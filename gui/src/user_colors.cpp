#include <wx/colour.h>
#include <wx/hashmap.h>

#include "user_colors.h"
#include "color_types.h"
#include "color_handler.h"
#include "s52plib.h"

ColorScheme global_color_scheme = GLOBAL_COLOR_SCHEME_DAY;

namespace user_colors {

ColorScheme GetColorScheme() { return global_color_scheme; }

static const char *const usercolors[] = {
    //======================================================================
    // Table:DAY - Modern dark theme inspired by Raymarine Axiom / B&G Zeus
    // Dark charcoal backgrounds with ocean-teal accent (#00BCD4)
    // Designed for maximum chart visibility and reduced eye strain
    //======================================================================
    "Table:DAY",

    // Standard palette colors - adjusted for dark background visibility
    "GREEN1; 80;220; 80;", "GREEN2; 45;170; 45;", "GREEN3; 40; 58; 40;",
    "GREEN4;  0;230;  0;", "GREEN5;150;230;  0;", "BLUE1; 100;130;220;",
    "BLUE2;  55; 75;190;", "BLUE3;  40; 80;255;", "GREY1;  58; 62; 70;",
    "GREY2;  44; 48; 56;", "RED1;   80; 44; 44;", "YELO1; 243;229; 47;",
    "YELO2; 180;120; 20;", "TEAL1;   0;188;212;",

    // Basic UI colors
    "UBLCK; 212;216;224;",  // Text/lines: light on dark background
    "UWHIT;  30; 32; 40;",  // Backgrounds: dark charcoal
    "URED;  255; 82; 82;",  // Own vessel: bright red, visible on dark
    "UGREN;  76;217; 100;",  // Green: slightly muted for dark bg
    "COMPT;  44; 48; 56",   // Compass rose background: dark

    // Dialog system colors - dark theme for all platforms
    "DILG0;  30; 32; 40;",  // Dialog window background: dark charcoal
    "DILG1;  40; 44; 52;",  // Selected items background: slightly lighter
    "DILG2;  24; 26; 32;",  // Control/input field background: deepest dark
    "DILG3; 212;216;224;",  // Dialog text: light grey for contrast
    /**
     * Text color optimized for progressively darker backgrounds (pairs with
     * DILG0). Gets progressively lighter as background darkens to maintain
     * contrast. Ideal for tooltips, overlays, and any text over DILG0
     * background. */
    "DILG4; 200;204;212;",
    "UITX1; 180;184;192;",  // Menu text: slightly dimmer light grey

    // Chart and information display colors
    "CHGRF; 100;110;120;",  // Chart gray foreground: medium grey on dark
    "CHYLW; 255;214;  0;",  // Chart yellow: brighter for dark bg visibility
    "CHWHT; 180;200;210;",  // Chart white: soft white for dark bg

    // Information status colors - vibrant for dark background
    "UINFM; 220; 100;220;",  // Magenta: brighter for dark bg
    "UINFG;  76; 217;100;",  // Green: vibrant status green
    "UINFR; 255;  82; 82;",  // Red: bright alert red
    "UINFF; 140;150;160;",  // Default foreground: medium grey
    "SHIPS; 160;170;180;",  // AIS target fills: visible on dark

    // Route and navigation colors
    "UDKRD; 180; 40; 30;",  // Dark red variant: visible on dark bg
    "UARTE; 255; 60; 60;",  // Active route: bright red on dark

    // Chart data and measurement colors
    "NODTA;  50; 55; 65;",   // No data areas: dark grey
    "CHBLK; 200;210;220;",   // Chart text/lines: light on dark
    "SNDG1; 140;150;160;",   // Sounding text primary: medium grey
    "SNDG2; 180;190;200;",   // Sounding text secondary: lighter grey
    "SCLBR;   0;188;212;",   // Scale bar: teal accent color

    // UI framework colors
    "UIBDR;  55; 60; 70;",   // UI borders: subtle dark border
    "UIBCK;  40; 44; 52;",   // Highlight backgrounds: dark surface
    "UINFB;   0;188;212;",   // Information blue: teal accent for active states
    "UINFD;  70; 76; 86;",   // Information dark: medium dark borders
    "UINFO; 255;171; 64;",   // Information orange: warm accent

    // Route planning colors
    "PLRTE; 255;100; 60;",  // Planned route: warm orange-red
    "CHMGD; 220;100;220;",  // Chart magenta: bright on dark

    // Dashboard instrument colors - dark panel, light readouts (B&G style)
    "DASHB;  26; 28; 36;",  // Dashboard background: deep dark
    "DASHL;  80; 88;100;",  // Dashboard labels: subtle grey
    "DASHF; 220;225;235;",  // Dashboard foreground: bright white text
    "DASHR; 255; 82; 82;",  // Dashboard red: bright alarm
    "DASHG;  76;217;100;",  // Dashboard green: healthy status
    "DASHN;   0;188;212;",  // Dashboard needle: teal accent
    "DASH1;  60; 70;100;",  // Dashboard graphics primary: dark blue-grey
    "DASH2;  45; 52; 72;",  // Dashboard graphics secondary: deeper
    "COMP1;  34; 38; 46;",  // Compass window background: dark

    // Window and canvas elements
    "GREY3;  22; 24; 30;",     // MUI toolbar background: near-black
    "BLUE4;   0;150;180;",     // Canvas focus bar: teal variant
    "VIO01; 190; 80;180;",     // Violet: brighter for dark bg
    "VIO02; 220;130;220;",     // Violet variant: lighter
    "BLUEBACK; 212;234;238;",  // Deep water: preserve chart rendering
    "LANDBACK; 201;185;122;",  // Land mass: preserve chart rendering

    //======================================================================
    // Table:DUSK - Reduced brightness twilight, darker than DAY dark theme
    // Further dimmed colors for transition to night vision
    //======================================================================
    "Table:DUSK", "GREEN1; 40;110; 40;", "GREEN2; 22; 85; 22;",
    "GREEN3; 25; 35; 25;", "GREEN4;  0;115;  0;", "BLUE1;  50; 65;110;",
    "BLUE2;  28; 38; 95;", "BLUE3;  20; 40;128;", "GREY1;  38; 42; 48;",
    "GREY2;  30; 34; 40;", "RED1;   50; 28; 28;", "UBLCK; 140;145;155;",
    "UWHIT;  20; 22; 28;", "URED;  120; 54; 11;", "UGREN;  35;110; 20;",
    "YELO1; 120;115; 24;", "YELO2;  90; 60;  0;", "TEAL1;   0; 94;106;",
    "GREEN5; 75;115; 0;", "COMPT;  30; 33; 38",

    "CHGRF;  60; 66; 72;", "UINFM; 110; 50;108;", "UINFG;  38;109; 50;",
    "UINFF;  70; 76; 82;", "UINFR; 128; 41; 41;", "SHIPS;  90;100;110;",
    "CHYLW; 128;109; 24;", "CHWHT;  90;100;105;",

    "DILG0;  22; 24; 30;",   // Dialog Background: deeper dark
    "DILG1;  28; 30; 38;",   // Selected Background
    "DILG2;  16; 18; 22;",   // Control Background
    "DILG3; 140;145;155;",   // Text: dimmer than DAY
    "DILG4; 120;125;135;",
    "UITX1; 100;106;116;",  // Menu text color
    "UDKRD;  90; 20; 15;",  // Dark red variant
    "UARTE; 128; 40; 40;",  // Active route

    "NODTA;  30; 34; 40;", "CHBLK; 110;120;130;", "SNDG1;  70; 76; 82;",
    "SNDG2;  90;100;105;", "SCLBR;   0; 94;106;", "UIBDR;  35; 40; 48;",
    "UINFB;   0; 94;106;", "UINFD;  45; 50; 58;", "UINFO; 128; 86; 32;",
    "PLRTE; 128; 50; 30;", "CHMGD; 110; 50;108;", "UIBCK; 16; 18; 22;",

    "DASHB;  16; 18; 24;",  // Dashboard Instr background
    "DASHL;  48; 54; 62;",  // Dashboard Instr Label
    "DASHF; 140;145;155;",  // Dashboard Foreground
    "DASHR; 128; 41; 41;",  // Dashboard Red
    "DASHG;  38;109; 50;",  // Dashboard Green
    "DASHN;   0; 94;106;",  // Dashboard Needle: dimmed teal
    "DASH1;  36; 42; 60;",  // Dashboard Illustrations
    "DASH2;  28; 32; 46;",  // Dashboard Illustrations
    "COMP1;  22; 24; 30;",  // Compass Window Background

    "GREY3;  14; 16; 20;",  // MUIBar/TB background
    "BLUE4;   0; 75; 90;",  // Canvas Focus Bar
    "VIO01; 95; 40; 90;", "VIO02; 110; 65;110;", "BLUEBACK; 186;213;235;",
    "LANDBACK; 201;185;122;",

    //======================================================================
    // Table:NIGHT - Ultra-dim for true night vision preservation
    // Red-shifted, minimal brightness, preserves dark adaptation
    //======================================================================
    "Table:NIGHT", "GREEN1; 20; 50; 20;", "GREEN2; 10; 40; 10;",
    "GREEN3;  8; 14;  6;", "GREEN4;  0; 44;  0;", "BLUE1;  30; 30; 60;",
    "BLUE2;  14; 14; 55;", "BLUE3;   0;  0; 30;", "GREY1;  24; 26; 30;",
    "GREY2;  16; 18; 22;", "RED1;   40; 20; 20;", "UWHIT;  12; 14; 18;",
    "UBLCK;  80; 82; 88;", "URED;   60; 20;  5;", "UGREN;  12; 40;  8;",
    "YELO1;  50; 48; 10;", "YELO2;  28; 18;  0;", "TEAL1;   0; 24; 28;",
    "GREEN5; 34; 48; 0;", "COMPT;  16; 18; 22",
    "DILG0;  12; 14; 18;",     // Dialog Background: near black
    "DILG1;  18; 20; 24;",     // Selected Background
    "DILG2;   6;  8; 10;",     // Control Background: deepest
    "DILG3;  80; 82; 88;",     // Text: dim for night vision
    "DILG4;  70; 72; 78;",
    "UITX1;  50; 54; 58;",  // Menu text color
    "UDKRD;  50;  8;  0;",  // Dark red variant
    "UARTE;  64; 20; 20;",  // Active route: dim red

    "CHGRF;  28; 32; 36;", "UINFM;  40; 14; 40;", "UINFG;  16; 36; 10;",
    "UINFF;  40; 44; 48;", "UINFR;  64; 20; 12;", "SHIPS;  50; 55; 60;",
    "CHYLW;  40; 38; 10;", "CHWHT;  44; 48; 52;",

    "NODTA;   8;  10;  12;", "CHBLK;  55;  60;  65;", "SNDG1;  40;  44;  48;",
    "SNDG2;  50;  55;  58;", "SCLBR;   0;  47;  53;", "UIBDR;  20;  22;  26;",
    "UINFB;   0;  47;  53;", "UINFD;  28;  32;  38;", "UINFO;  64;  34;  12;",
    "PLRTE;  64;  22;  12;", "CHMGD; 40; 14; 40;", "UIBCK;  8; 10; 12;",

    "DASHB;   6;  8; 10;",  // Dashboard Instr background: near black
    "DASHL;  24; 26; 30;",  // Dashboard Instr Label
    "DASHF;  70; 72; 78;",  // Dashboard Foreground: dim
    "DASHR;  64; 20; 12;",  // Dashboard Red: dim
    "DASHG;  12; 50; 12;",  // Dashboard Green: dim
    "DASHN;   0; 47; 53;",  // Dashboard Needle: dim teal
    "DASH1;  20; 24; 36;",  // Dashboard Illustrations
    "DASH2;  14; 16; 26;",  // Dashboard Illustrations
    "COMP1;  10; 12; 16;",  // Compass Window Background

    "GREY3;   6;  8; 10;",  // MUIBar/TB background: near black
    "BLUE4;   0; 38; 44;",  // Canvas Focus Bar: dim teal
    "VIO01;  48; 12; 44;", "VIO02;  64; 20; 60;", "BLUEBACK; 186;213;235;",
    "LANDBACK; 201;185;122;",

    "*****"};

static wxArrayPtrVoid *UserColorTableArray = 0;
static wxArrayPtrVoid *UserColourHashTableArray;

static int get_static_line(char *d, const char *const *p, int index, int n) {
  if (!strcmp(p[index], "*****")) return 0;

  strncpy(d, p[index], n);
  return strlen(d);
}

void Initialize() {
  const char *const *p = usercolors;
  char buf[81];
  int index = 0;
  char TableName[20];
  colTable *ctp;
  colTable *ct;
  int R, G, B;

  UserColorTableArray = new wxArrayPtrVoid;
  UserColourHashTableArray = new wxArrayPtrVoid;

  //    Create 3 color table entries
  ct = new colTable;
  ct->tableName = new wxString("DAY");
  ct->color = new wxArrayPtrVoid;
  UserColorTableArray->Add((void *)ct);

  ct = new colTable;
  ct->tableName = new wxString("DUSK");
  ct->color = new wxArrayPtrVoid;
  UserColorTableArray->Add((void *)ct);

  ct = new colTable;
  ct->tableName = new wxString("NIGHT");
  ct->color = new wxArrayPtrVoid;
  UserColorTableArray->Add((void *)ct);

  while ((get_static_line(buf, p, index, sizeof(buf) - 1))) {
    if (!strncmp(buf, "Table", 5)) {
      sscanf(buf, "Table:%s", TableName);

      for (unsigned int it = 0; it < UserColorTableArray->GetCount(); it++) {
        ctp = (colTable *)(UserColorTableArray->Item(it));
        if (!strcmp(TableName, ctp->tableName->mb_str())) {
          ct = ctp;
          break;
        }
      }

    } else {
      char name[21];
      int j = 0;
      while (buf[j] != ';' && j < 20) {
        name[j] = buf[j];
        j++;
      }
      name[j] = 0;

      S52color *c = new S52color;
      strcpy(c->colName, name);

      sscanf(&buf[j], ";%i;%i;%i", &R, &G, &B);
      c->R = (char)R;
      c->G = (char)G;
      c->B = (char)B;

      ct->color->Add(c);
    }

    index++;
  }

  //    Now create the Hash tables

  for (unsigned int its = 0; its < UserColorTableArray->GetCount(); its++) {
    wxColorHashMap *phash = new wxColorHashMap;
    UserColourHashTableArray->Add((void *)phash);

    colTable *ctp = (colTable *)(UserColorTableArray->Item(its));

    for (unsigned int ic = 0; ic < ctp->color->GetCount(); ic++) {
      S52color *c2 = (S52color *)(ctp->color->Item(ic));

      wxColour c(c2->R, c2->G, c2->B);
      wxString key(c2->colName, wxConvUTF8);
      (*phash)[key] = c;
    }
  }

  //    Establish a default hash table pointer
  //    in case a color is needed before ColorScheme is set
  pcurrent_user_color_hash =
      (wxColorHashMap *)UserColourHashTableArray->Item(0);
}
void DeInitialize() {
  if (!UserColorTableArray) return;
  for (unsigned i = 0; i < UserColorTableArray->GetCount(); i++) {
    colTable *ct = (colTable *)UserColorTableArray->Item(i);

    for (unsigned int j = 0; j < ct->color->GetCount(); j++) {
      S52color *c = (S52color *)ct->color->Item(j);
      delete c;  // color
    }

    delete ct->tableName;  // wxString
    delete ct->color;      // wxArrayPtrVoid

    delete ct;  // colTable
  }

  delete UserColorTableArray;

  for (unsigned i = 0; i < UserColourHashTableArray->GetCount(); i++) {
    wxColorHashMap *phash = (wxColorHashMap *)UserColourHashTableArray->Item(i);
    delete phash;
  }

  delete UserColourHashTableArray;
}

wxColorHashMap *GetMapByScheme(const std::string &scheme_name) {
  unsigned Usercolortable_index = 0;
  for (unsigned int i = 0; i < UserColorTableArray->GetCount(); i++) {
    colTable *ct = (colTable *)UserColorTableArray->Item(i);
    if (scheme_name == (*ct->tableName)) {
      return (wxColorHashMap *)UserColourHashTableArray->Item(i);
    }
  }
  return nullptr;
}

wxColor GetDimColor(wxColor c) {
  if ((global_color_scheme == GLOBAL_COLOR_SCHEME_DAY) ||
      (global_color_scheme == GLOBAL_COLOR_SCHEME_RGB))
    return c;

  float factor = 1.0;
  if (global_color_scheme == GLOBAL_COLOR_SCHEME_DUSK) factor = 0.5;
  if (global_color_scheme == GLOBAL_COLOR_SCHEME_NIGHT) factor = 0.25;

  wxImage::RGBValue rgb(c.Red(), c.Green(), c.Blue());
  wxImage::HSVValue hsv = wxImage::RGBtoHSV(rgb);
  hsv.value = hsv.value * factor;
  wxImage::RGBValue nrgb = wxImage::HSVtoRGB(hsv);

  return wxColor(nrgb.red, nrgb.green, nrgb.blue);
}

}  // namespace user_colors
