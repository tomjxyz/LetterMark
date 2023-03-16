// Text area and output area variables
let ta, oa;

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
    for (line of source)
    {
        let plain = false;
        // let inline = false;
        // console.log(line.slice(-1));
        // if (line.slice(-1) === '\\' && line.slice(-2) !== '\\\\')
        // {
        //     line = line.substring(0, line.length - 1);
        //     inline = true;
        //     prevInline = true;
        // }
        // else if (line.slice(-2) === '\\\\')
        // {
        //     line = line.substring(0, line.length - 1);
        // }


        let elm, text;
        text = line.substring(3);
        switch (line.substring(0, 3)) {
            case '.b ':
                elm = document.createElement('b');
                elm.innerText = text;
                break;
            case '.i ':
                elm = document.createElement('i');
                elm.innerText = text;
                break;
            case '.h ':
                elm = document.createElement('h1');
                elm.innerText = text;
                break;
            case '.s ':
                elm = document.createElement('h3');
                elm.innerText = text;
                break;
            case '.a ':
                elm = document.createElement('a');
                elm.innerText = text;
                elm.href = text;
                break;
            case '.m ':
                elm = document.createElement('img');
                elm.src = text;
                break;
            case '.c ':
                elm = document.createElement('span');
                elm.style.fontFamily = 'monospace';
                elm.innerText = text;
                break;
            case '.q ':
                elm = document.createElement('i');
                elm.innerText = `   "${text}"`;
                break;

            default:
                plain = true;
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
        // if (inline) {elm.style.display = 'inline';}
        oa.append(elm);
    }
}

document.addEventListener('keyup', render);