# Prompt Utils

Little utilities written in C to pretty up my shell prompt.

*Note* All problems solved by these tools could easily be solved by small shell
scripts -- but where is your sense of adventure?


## Installation


```
make && sudo make install
```

Defaults installing to `/usr/local/bin`. Set `PREFIX` environment variable to
change `/usr/local` to your liking.

## Usage

### gitst
Shows current git branch
```
$ gitst
(master)
```

### swd
Prints an abbreviated single letter path to your current working dir
```
$ cd /home/wnh/projects/prompt_utils
$ swd
~/p/prompt_utils
```

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## Credits

Me!

## License

BSD. See `LICENCE`



