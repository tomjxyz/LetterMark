// Text area and output area variables
let ta, oa;
let list = false;
let listelm;

// Assign once page loaded
document.addEventListener('DOMContentLoaded', function (e) {
    ta = document.querySelector('textarea');
    oa = document.querySelector('.render');
    render();
});

// Handler for each keypress
function render() {
    oa.innerHTML = '';
    const source = ta.value.split('\n');
    for (linenum = 0; linenum < source.length; linenum++) 
    {
        let line = source[linenum];
        let plain = false;

        let elm, text;
        text = line.substring(3);
        switch (line.substring(0, 3)) {
            case '.b ':
                list = false;
                elm = document.createElement('b');
                elm.innerText = text;
                break;
            case '.i ':
                list = false;
                elm = document.createElement('i');
                elm.innerText = text;
                break;
            case '.h ':
                list = false;
                elm = document.createElement('h1');
                elm.innerText = text;
                break;
            case '.s ':
                list = false;
                elm = document.createElement('h3');
                elm.innerText = text;
                break;
            case '.a ':
                list = false;
                elm = document.createElement('a');
                elm.innerText = text;
                elm.href = text;
                break;
            case '.m ':
                list = false;
                elm = document.createElement('img');
                elm.src = text;
                break;
            case '.c ':
                list = false;
                elm = document.createElement('span');
                elm.style.fontFamily = 'monospace';
                elm.innerText = text;
                break;
            case '.q ':
                list = false;
                elm = document.createElement('i');
                elm.innerText = text;
                elm.className = 'quote';
                break;
            case '.l ':
                if (!list)
                {
                    list = true;
                    listelm = document.createElement('ul');
                    oa.append(listelm);
                }
                elm = document.createElement('li');
                elm.innerText = text;
                break;
            case '.o ':
                if (!list)
                {
                    list = true;
                    listelm = document.createElement('ol');
                    oa.append(listelm);
                }
                elm = document.createElement('li');
                elm.innerText = text;
                break;              

            default:
                plain = true;
                list = false;
                break;
        }
        if (plain)
        {
            if (line === "")
            {
                elm = document.createElement('br');
            }
            else 
            {
                elm = document.createElement('span');
                elm.innerText = line;
            }
        }

        if (line.slice(-1) === '/')
        {
            elm.style.display = 'inline';
            elm.innerText = elm.innerText.slice(0, -1);
        }
        if (source.length > 1 && linenum > 0)
        {
            if (source[linenum-1].slice(-1) === '/')
            {
                elm.style.display = 'inline';
            }
        }

        if (!list){
            oa.append(elm);
        } else {
            listelm.append(elm);
        }

    }
}

document.addEventListener('keyup', render);