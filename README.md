# `sudo su` Phishing

It is well known that requiring the user password for the `sudo` command offers little protection
against attackers who have already compromised a privileged `sudoer` account. Attackers can easily
replace the sudo command with a malicious version, intercepting passwords as users attempt to
execute privileged commands.

Here, I present a new "privilege escalation" technique to gain root access from an unprivileged
application account by intercepting the `sudo su` command, which is commonly used to switch to
another user account. While this technique is much more limited, it can be highly effective against
certain server configurations.

A common server setup involves a privileged system administrator account (e.g. `sysadmin`), and a
separate unprivileged account (e.g. `app`) to securely run an application. When an action needs to
be completed by the unprivileged account, the administrator may switch to this account using
`sudo su` (e.g. `sudo su app`) and then enter the password. If the unprivileged account is
compromised, the attacker may update `.bashrc`, or some other file, to initially display a message
telling the user the password used for the `sudo su` command is incorrect. In response, the user is
likely to type in the password a second time, at which point the password can be logged and used to
both gain access to the privileged account and to the `root` account.
