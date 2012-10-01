void grabkeys(void) {
  if(keymode == INSERTMODE) {
    defgrabkeys();
  } else {
    XUngrabKey(dpy, AnyKey, AnyModifier, root);
    // grab all keys while not in insert mode
    XGrabKey(dpy, AnyKey, AnyModifier, root,
        True, GrabModeAsync, GrabModeAsync);
  }
}

void keypress(XEvent *e) {
  int handled = False;
  int i;
  unsigned int changetags = 0;
  Arg a;

  if(keymode == INSERTMODE)
  {
    defkeypress(e);
  }
  else
  {
    XKeyEvent *ev = &e->xkey;
    KeySym keysym = XKeycodeToKeysym(dpy, (KeyCode)ev->keycode, 0);
    switch(keymode)
    {
      case VIEWMODE:
      case TOGGLEVIEWMODE:
      case TAGMODE:
      case TOGGLETAGMODE:
      case RENAMETAGMODE:
        for(i = 0; i < LENGTH(tagkeys); i++)
        {
          if(keysym == tagkeys[i].keysym)
          {
            changetags = tagkeys[i].tags;
            break;
          }
        }
    }
    switch(keymode)
    {
      case VIEWMODE:              
        if(!changetags)
          break;
        handled = True;
        a.ui = changetags;        
        view(&a);                 
        break;                    
      case TOGGLEVIEWMODE:
        if(!changetags)
          break;
        handled = True;
        a.ui = changetags;
        toggleview(&a);
        break;
      case TAGMODE:               
        { 
          if(!changetags)
            break;
          handled = True;
          Client *oldsel = selmon->sel;
          a.ui = changetags;
          tag(&a);
          if(selmon->sel != oldsel)
          { 
            a.ui = INSERTMODE;
            setkeymode(&a);
          } 
          break;
        } 
      case TOGGLETAGMODE:         
        { 
          if(!changetags)
            break;
          handled = True;
          Client *oldsel = selmon->sel;
          a.ui = changetags;      
          toggletag(&a);          
          if(selmon->sel != oldsel)
          {
            a.ui = INSERTMODE;
            setkeymode(&a);
          }
          break;
        } 
      case RENAMETAGMODE:
        {
          if(!changetags)
            break;
          // find the tag index
          renametag = -1;
          for(i = 0; i < 32; i++)
          {
            if(changetags & 1)
            {
              if(changetags >> 1)
              {
                // not a valid single tag, as changetags has more than one bit
                // in its mask
                break;
              }
              renametag = i;
              break;
            }
            changetags >>= 1;
          }
          if(renametag == -1)
            break;
          if(renamed_tags[renametag] == NULL)
          {
            renamed_tags[renametag] = malloc(256);
            tags[renametag] = renamed_tags[renametag];
          }
          sprintf(renamed_tags[renametag], "%s:", original_tags[renametag]);
          updatebars();
          keymode = RENAMETAG_INPUT;
          handled = True;
          break;
        }
      case RENAMETAG_INPUT:
        {
          for(i = 0; i < 255; i++)
          {
            if(tags[renametag][i] == '\0')
              break;
          }
          if(i == 255)
            break;
          if((keysym >= 0x00) && (keysym <= 0x007e))
          {
            renamed_tags[renametag][i] = keysym;
            renamed_tags[renametag][i+1] = '\0';
            updatebars();
            handled = True;
          }
          switch(keysym)
          {
            case XK_BackSpace:
              if(i != 0)
                renamed_tags[renametag][i - 1] = '\0';
              updatebars();
              handled = True;
              break;
            case XK_Shift_L:
            case XK_Shift_R:
            case XK_Caps_Lock:
              handled = True;
              break;
          }
          if(!handled && i == 0)
          {
            free(renamed_tags[renametag]);
            renamed_tags[renametag] = NULL;
            tags[renametag] = original_tags[renametag];
            updatebars();
          }
          break;
        }
    }
    if(!handled)
    {
      // any key not handled (e.g. ESC) will return the user to insert mode
      a.ui = INSERTMODE;
      setkeymode(&a);
    }
  }
}

void setkeymode(const Arg *arg) {
  if(!arg)
    return;
  keymode = arg->ui;
  grabkeys();
}
