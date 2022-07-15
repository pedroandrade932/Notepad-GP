#---- Imports ----
import webbrowser
import PySimpleGUI as sg
import pathlib

#---- Abre as configurações. ----
dados = []

def save():
    arquivo = open('__data__/config.txt', 'wt+')
    arquivo.write('{}\n'.format(tema))
    arquivo.write('{}\n'.format(font_size))
    arquivo.write('{}\n'.format(first))
    arquivo.close()


def openf():
    global tema, font_size, first
    arquivo = open('__data__/config.txt', 'r')
    for l in arquivo:
        l = l.rstrip()
        dados.append(l)
    arquivo.close()
    if dados[0] != '':
        tema = dados[0]
        font_size = int(dados[1])
        first = dados[2]


first = 'True'
tema = 'reddit'
font_size = 12
try:
    openf()
except FileNotFoundError:
    save()

sg.ChangeLookAndFeel(tema)

#---- Variáveis Globais. ----
WIN_W = 90
WIN_H = 25
START_UP = True
filename = None

file_new = 'New file............(CTRL+N)'
file_open = 'Open file...........(CTRL+O)'
file_save = 'Save file...........(CTRL+S)'

#---- Layouts. ----

#--- Layout do menu. ---
menu_layout = [

    ['File', [file_new, file_open, file_save, 'Save as', '---', 'Exit']],
    ['Settings', ['Preferences',]],
    ['Tools', ['Word Count', 'Line Count',]],
    ['Help', ['Manual', 'About']]

]

#--- Layout da tela. ---
layout = [

    [sg.Menu(menu_layout)],
    [sg.Text('> New File <', size=(WIN_W,1), font=('Consolas', 12), key='__INFO__')],
    [sg.Multiline(size=(WIN_W,WIN_H), font=('Consolas', font_size), key='__BODY__')]

]

#---- Configurações da janela. ----
window = sg.Window('GP Notepad.', layout, margins=(0,0), resizable=True, 
return_keyboard_events=True, icon='__icones__/Notepad.png')

#---- DEFS. ----

def new_file():
    '''Reset body and info bar, and clear filename variable'''
    window['__BODY__'].update(value='')
    window['__INFO__'].update(value='> New File <')
    file = None
    return file


def open_file():
    '''Open file and update the infobar'''
    filename = sg.popup_get_file('Open', no_window=True, initial_folder='GPDocuments/')
    if filename:
        file = pathlib.Path(filename)
        window['__BODY__'].update(value=file.read_text())
        window['__INFO__'].update(value=file.absolute())
        return file


def save_file(file):
    '''Save file instantly if already open; otherwise use `save-as` popup'''
    if file:
        file.write_text(values.get('__BODY__'))
    else:
        save_file_as()


def save_file_as():
    '''Save new file or save existing file with another name'''
    filename = sg.popup_get_file('Save As', save_as=True, no_window=True, 
    default_extension='.txt', default_path='Document', initial_folder='GPDocuments/')
    if filename:
        file = pathlib.Path(filename)
        file.write_text(values.get('__BODY__'))
        window['__INFO__'].update(value=file.absolute())
        return file


def word_count():
    '''Display estimated word count'''
    words = [w for w in values['__BODY__'].split(' ') if w!='\n']
    word_count = len(words)
    sg.popup_no_wait('Word Count: {:,d}'.format(word_count))


def line_count():
    '''Display estimated line count'''
    lines = [w for w in values['__BODY__'].split('\n') if w!=' ']
    line_count = len(lines)
    sg.popup_no_wait('Line Count: {:,d}'.format(line_count))



def about_me():
    '''A short, pithy quote'''
    sg.popup_no_wait('Text editor created by Pedro Gabriel Holanda Andrade.')


br = False
def conf():
    global tema, br, font_size
    layout = [
        [sg.Text('Settings. (Reinicie o programa para salvar)')],
        [sg.Text('')],
        [sg.Text('Lista de temas.')],
        [sg.Listbox(['LightBlue1', 'LightBlue4', 'Reddit', 'LightGreen', 'TanBlue', 'Python', 'DarkBLue1', 'DarkBLue4', 'DarkGrey14', 'DarkBrown1', 'DarkBrown2', 'DarkBrown3'], size=(24,6), key='-BOX-')],
        [sg.Text('')],
        [sg.Text('Font size: '), sg.Input('', (5,1), key='font')],
        [sg.Text('')],
        [sg.Button('Save'), sg.Button('Cancel')]
    ]
    window = sg.Window('Settings', layout, icon='__imagens__/Engre.png')
    while True:
        button, values = window.read()
        if button == sg.WINDOW_CLOSED:
            window.close()
            break
        if button == 'Save':
            if values['font'] == '':
                values['font'] = font_size
            font_size = int(values['font'])
            tema = values['-BOX-'][0]
            save()
            window.close()
            br = True
            break
        if button == 'Cancel':
            window.close()

swindow = ''
#---- Eventos. ----
while True:
    
    event, values = window.read(timeout=1)

    if START_UP:
        window['__BODY__'].expand(True, True)
        START_UP = False
    
    if first == 'True':
        sg.popup('Welcome!!!', 
        'Welcome to GP Notepad, where you can edit your texts and save them. ', 
        'If you have questions about how to use GP, go to \nHelp > Manual.', text_color='red')
        first = 'False'
    
    if event in (None, 'Exit'):
        save()
        break
    if event in (file_new, 'n:78'):
        filename = new_file()
    if event in (file_open, 'o:79'):
        filename = open_file()
    if event in ('Save as'):
        filename = save_file_as()
    if event in (file_save, 's:83'):
        save_file(filename)
    if event in ('Word Count',):
        word_count()
    if event in ('Line Count',):
        line_count()
    if event in ('Manual',):
        webbrowser.open_new('manual.html')
    if event in ('About',):
        about_me()
    if event in ('Preferences',):
        conf()
        if br == True:
            break
